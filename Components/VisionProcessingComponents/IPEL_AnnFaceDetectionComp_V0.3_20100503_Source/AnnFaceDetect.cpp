/*
축소된 영상은 Gaussian filter를 가지고 smooth하게 되어 noise를 줄인다. 그리고 나서 검색은 
classification process 전에 histogram equalized된 19x19 rectangles을 사용한다.
19x19 matrix로부터 합쳐져 만들어진 361차원의 컬럼 벡터의 차원을 줄이기 위해, orthogonal PCA, LDA 
or non-orthogonal ICA projection matrix 선형적으로 프로젝트하게 된다. 그 컬럼은 동일한 차원의 
projection basis vectors. Projection matrix에서 training faces/non-faces set에서 구한 PCA transform에서
얻은 40 eigenvectors가 사용된다. 

PCA, LDA and ICA transforms에 대해 전체적으로 약1800개의 face vectors과 34000개의 non-faces 
vectors들이 사용된다. 그 변환에 사용되는 matrix은 35800x361 size이다. 40개의 dimensional training 
samples은 나중에 361x40 PCA, LDA ,ICA로 프로젝트되며, 이 projection matrix 후에 ANN classifier를 
train 하기 위해 사용되는데, 각각 40, 20, 10 and 1 neurons의 4 layers들로 구성된다.
Red color는 face data이며, green color는 nonface data이다. 

ANN training procedure에서는 1800 faces and 34000 non-faces영상을 반으로 나누어 반은 training set으로
다른 반은 validation and test sets으로 사용했다. ANN알고리즘으로는 ANN backpropagation gradient descent
training algorithm with momentum and adaptive learning rate을 사용했다.
*/

/*
Motion Detection
비디어 영상에서 temporal information을 이용하여 얼굴 영역을 검사하는 시간을 줄일 수 있다.
영상 프레임에서 difference를 유지하는 간단한 motion detector class를 사용하여 영역을 검사한다.
미리 검출된 영역을 놓치지 않기위해 전에 찾은 얼굴 영역을 마크해 놓고 다음 영상에서 그 영역을 찾도록 한다.

Skin Detection
skin 영역을 검출하기 위해 RGB 데이터로부터 컬러 정보를 가져와 사용한다. 
너무 어둡지 않고 조명이 충분하다면, 얼굴영상 부분 중에서 blue, green 컬러 영역은 볼 필요가 없을 것이다.
현재 여기서 사용된 skin은 백인을 위주로 구성이 되어 있다. 다민족의 영상이 충분하지 않아 skin에 대한
데이터가 다양하지 않다. non-skin data는 background colored pictures로 사용됬다. color data는 r,g,b의 
3채널값을 갖는 3차원 vector로 구성됬다. 그것은 스케일이 0부터 1까지 조정된다.
ANN classifier는 3 layers와 3, 6 and 1 neurons으로 구성된 것을 사용한다.
*/

/*
  Remember to remove skin.nn if the lighting conditions are bad. 
  If you are still not detected, remove SVM preflt.nn pre-filter.
*/

#include <math.h>
#include <float.h>

#include "vec2D.h"
#include "vec2Dc.h"
#include "annetwork.h"
#include "aiclassifier.h"
#include "imageframe.h"
#include "AnnFaceDetect.h"
#include "OprosPrintMessage.h"

AnnFaceDetect::AnnFaceDetect() : m_status(-1), m_dx(0), m_dy(0), m_status_of_classifiers(0),
			       m_face_rectangle(0), m_face_vector(0), m_projected_face(0),
			       m_motion_amount(-1.0f), m_skin_amount(-1.0f), 
			       m_skin_mask(0), m_tmp_skin_mask(0), m_skin_filter(0),
			       m_preface_filter(0), m_projection_matrix(0), m_face_classifier(0) 
{
	m_histogram = new vec2D(1, 256);
}	

AnnFaceDetect::~AnnFaceDetect()
{
	delete m_histogram;

	if (m_face_rectangle != 0) delete m_face_rectangle;
	if (m_face_vector != 0) delete m_face_vector;	
	if (m_skin_mask != 0)
	{
		delete m_skin_mask;
		delete m_tmp_skin_mask;
	}

	unload_skin_filter();
	unload_preface_filter();
	unload_face_classifier();
	unload_projection_matrix();

	clear_faces();
}

void AnnFaceDetect::init(unsigned int image_width, unsigned int image_height,
			unsigned int face_width, unsigned int face_height, 
			const float* scales, unsigned int nscales)
{
	if (m_face_rectangle != 0) delete m_face_rectangle;
	m_face_rectangle = new vec2D(face_height, face_width);

	if (m_face_vector != 0) delete m_face_vector;
	m_face_vector = new vec2D(1, face_height * face_width);

	if (m_skin_mask != 0) {
		delete m_skin_mask;
		delete m_tmp_skin_mask;
	}
	m_skin_mask = new vec2Dc(image_height, image_width);
	m_tmp_skin_mask = new vec2Dc(image_height, image_width);

	m_dx = (face_width - 1) / 2;
	m_dy = (face_height - 1) / 2;

	m_pyramid.init(image_width, image_height, scales, nscales);
	
	m_status = 0;
}

int AnnFaceDetect::load_skin_filter(const wchar_t* fname)
{
	unload_skin_filter();
	
	m_skin_filter = new AIClassifier(fname);

	if (m_skin_filter->status() == 0)
		m_status_of_classifiers |= SKINAI_BIT;
	
	return m_skin_filter->status();
}

void AnnFaceDetect::unload_skin_filter()
{
	if (m_skin_filter != 0) {
		delete m_skin_filter;
		m_skin_filter = 0;
		m_status_of_classifiers &= ~SKINAI_BIT;
	}
}

int AnnFaceDetect::load_preface_filter(const wchar_t* fname)
{
	unload_preface_filter();
	m_preface_filter = new AIClassifier(fname);

	if (m_preface_filter->status() == 0)
		m_status_of_classifiers |= PREFACEAI_BIT;
	
	return m_preface_filter->status();
}

void AnnFaceDetect::unload_preface_filter()
{
	if (m_preface_filter != 0) 
	{
		delete m_preface_filter;
		m_preface_filter = 0;
		m_status_of_classifiers &= ~PREFACEAI_BIT;
	}
}

int AnnFaceDetect::load_projection_matrix(const wchar_t* fname)
{
	unload_projection_matrix();
	m_projection_matrix = new ANNetwork(fname);
	if (m_projection_matrix->status() == 0) 
	{
		m_projected_face = new vec2D(1, m_projection_matrix->output_size());
		m_status_of_classifiers |= PRJMAT_BIT;
	}
	return m_projection_matrix->status();
}

void AnnFaceDetect::unload_projection_matrix()
{
	if (m_projection_matrix != 0) 
	{
		delete m_projected_face;
		m_projected_face = 0;
		delete m_projection_matrix;
		m_projection_matrix = 0;
		m_status_of_classifiers &= ~PRJMAT_BIT;
	}
}
	
int AnnFaceDetect::load_face_classifier(const wchar_t* fname)
{
	unload_face_classifier();
	m_face_classifier = new AIClassifier(fname);
	if (m_face_classifier->status() == 0)
		m_status_of_classifiers |= FACEAI_BIT;
	return m_face_classifier->status();
}

void AnnFaceDetect::unload_face_classifier()
{
	if (m_face_classifier != 0) 
	{
		delete m_face_classifier;
		m_face_classifier = 0;
		m_status_of_classifiers &= ~FACEAI_BIT;
	}
}

void AnnFaceDetect::clear_faces()
{
	for (unsigned int i = 0; i < get_faces_number(); i++)
		delete m_faces[i].face;
	m_faces.clear();
}


/*
    y - Gray image
    r,g,b - R,G,B components for skinfilter    
*/
int AnnFaceDetect::detect(const vec2D* y, char** r, char** g, char** b, const vec2Dc* search_mask)
{
	if (m_status < 0) return m_status;	

	estimate_motion_percent(search_mask);

	m_skin_amount = -1.0f;
	const vec2Dc* pskin_mask = 0;
	
	//optional skin filter
	if ((r != 0 && g != 0 && b != 0) && m_skin_filter != 0 && 
			m_skin_filter->status() == 0 && m_skin_filter->input_dimension() == 3) 
	{
	    skin_filter(r, g, b, search_mask);
	    pskin_mask = m_skin_mask;
	}		
		
	//build pyramid of images
	for (unsigned int i = 0; i < m_pyramid.get_frames_number(); i++)
	    m_pyramid.get_frame(i)->load_frame(y, search_mask, pskin_mask);	
	
	if (m_projection_matrix == 0 || m_face_classifier == 0) return -2;
	if (m_face_classifier->input_dimension() != m_projection_matrix->output_size()) return -3;

	run_classifiers();

	return search_faces();
}

void AnnFaceDetect::run_classifiers()
{
	float ovec;

	int w2 = m_face_rectangle->width() / 2;
	int h2 = m_face_rectangle->height() / 2;

	bool prefilter = false;
	if (m_preface_filter != 0 && m_preface_filter->input_dimension() == m_face_rectangle->length())
		prefilter = true;

	for (unsigned int i = 0; i < m_pyramid.get_frames_number(); i++) {
		const vec2D& my = *m_pyramid.get_frame(i)->get_y_blured();
		vec2D& face_map = *m_pyramid.get_frame(i)->get_face_map();
		const vec2Dc& search_map = *m_pyramid.get_frame(i)->get_search_map();

		face_map.set(0.0f);
		for (unsigned int y = get_dy(); y < my.height() - get_dy(); y++) {
			for (unsigned int x = get_dx(); x < my.width() - get_dx(); x++) {								
				// negotiate with [motion & skin detector out]
				if (search_map(y, x) == 0) continue;

				if (m_face_rectangle->copy(my, x - w2, y - h2)) {  //copy from left,top offsets
					m_face_rectangle->histeq(*m_histogram);

					for (unsigned int m = 0; m < m_face_rectangle->length(); m++)
						(*m_face_vector)(0, m) = (*m_face_rectangle)[m];

					if (prefilter == true) {
						if (m_preface_filter->classify(&(*m_face_vector)(0, 0), &ovec) < 0)  //non-face							
							continue;						
					}

					//project to low dimension
					m_projection_matrix->classify(&(*m_face_vector)(0, 0), &(*m_projected_face)(0, 0));
					//classify projecte data
					m_face_classifier->classify(&(*m_projected_face)(0, 0), &face_map(y, x));
				}
				//else failed to copy
				// ovec=0.0f;
			}
		}
		//debug
		//face_map.print(L"face_map.txt");
	}
}

unsigned int AnnFaceDetect::search_faces()
{
	ImageFrame* pframe = 0;

	FACERECT face_rect;
	RECT rect;
	face_rect.face=0;

	clear_faces();

	float max = 0.0f, tmpmx = 0.0f, zoom = 0.0f;
	unsigned int x = 0, y = 0, index = 0;
	int tmpx = 0, tmpy = 0;
	unsigned int w2 = m_face_rectangle->width() / 2;
	unsigned int h2 = m_face_rectangle->height() / 2;

	//debug out only
	for (unsigned int i = 0; i < m_pyramid.get_frames_number(); i++)
		m_pyramid.get_frame(i)->get_tmp_face_map()->copy(*m_pyramid.get_frame(i)->get_face_map());
	//debug out only

	while (true) {

		max = -FLT_MAX;
		index = 0;
		for (unsigned int i = 0; i < m_pyramid.get_frames_number(); i++) {
			pframe = m_pyramid.get_frame(i);
			pframe->get_face_map()->maxval(tmpmx, tmpx, tmpy, 3, 3, m_dx, m_dy);
			if (tmpmx > max) {
				index = i;
				max = tmpmx;
				x = tmpx;
				y = tmpy;
			}
		}

		pframe = m_pyramid.get_frame(index);
		zoom = pframe->get_zoom(); 
		if (max > 6.0f*0.8f + 3.0f*0.15f) { //3x3 positives	     //6 positives + 3 negatives in 3x3 box

			rect.left = (int)(float(x - w2) / zoom);
			rect.top = (int)(float(y - h2) / zoom);
			rect.right = (int)(float(x + w2) / zoom);
			rect.bottom = (int)(float(y + h2) / zoom);
			
			face_rect.rect = rect;
			face_rect.x = (unsigned int)(float(x) / zoom);
			face_rect.y = (unsigned int)(float(y) / zoom);
			face_rect.diag = sqrt(pow((float(w2) / zoom), 2.0f) + pow((float(h2) / zoom), 2.0f));

			if (is_foundface_overlaps(face_rect) == false) {
				face_rect.face = new vec2D(m_face_rectangle->height(), m_face_rectangle->width());
				face_rect.face->copy(*pframe->get_y(), x - w2, y - h2);
				face_rect.face->normalize(0.0f, 1.0f);
				m_faces.push_back(face_rect);
				erase_face_rect(rect);	    //erase found face region  [left, right)
			} 
			else {
				erase_face_rect((unsigned int)((float)x / zoom), (unsigned int)((float)y / zoom));
			}
		} else
			break;
	}

	return (unsigned int)m_faces.size();
}

void AnnFaceDetect::erase_face_rect(const RECT& r)
{
	RECT zr;
	for (unsigned int i = 0; i < m_pyramid.get_frames_number(); i++) {
		ImageFrame* pframe = m_pyramid.get_frame(i);
		float zoom = pframe->get_zoom();

		zr.left = int((float)r.left * zoom);
		zr.top = int((float)r.top * zoom);
		zr.right = int((float)r.right * zoom) + 1;
		zr.bottom = int((float)r.bottom * zoom) + 1;
		
		pframe->get_face_map()->set(0.0f, zr);   //[left, right)			      
	}
}
void AnnFaceDetect::erase_face_rect(unsigned int x, unsigned int y)
{
	RECT zr;
	int tmpx, tmpy;
	for (unsigned int i = 0; i < m_pyramid.get_frames_number(); i++) {
		ImageFrame* pframe = m_pyramid.get_frame(i);
		float zoom = pframe->get_zoom();

		tmpx = int((float)x * zoom);
		tmpy = int((float)y * zoom);
		zr.left = tmpx - 2;
		zr.top = tmpy - 2;
		zr.right = (tmpx + 2) + 1;
		zr.bottom = (tmpy + 2) + 1;

		pframe->get_face_map()->set(0.0f, zr);   //[left, right)		
	}
}

bool AnnFaceDetect::is_foundface_overlaps(const FACERECT& fr) const
{
	for (unsigned int i = 0; i < (unsigned int)m_faces.size(); i++) {
		const FACERECT* pfr = &m_faces[i];
		//euclid distanse between centers
		float dist = sqrt(pow((float(pfr->x) - float(fr.x)), 2)
				   + pow((float(pfr->y) - float(fr.y)), 2));
		if (dist <= 0.90f * (fr.diag + pfr->diag))
			return true;
	}
	return false;
}





void AnnFaceDetect::estimate_motion_percent(const vec2Dc* search_mask)
{
	if (search_mask == 0)
		m_motion_amount = -1.0f;
	else {
		unsigned int motion_pixels = 0;
		unsigned int total_pixels = 0;
		for (unsigned int y = get_dy(); y < search_mask->height() - get_dy(); y++) {
			for (unsigned int x = get_dx(); x < search_mask->width() - get_dx(); x++) {
				total_pixels++;
				if ((*search_mask)(y, x) == 1)
					motion_pixels++;
			}
		}
		m_motion_amount = float(motion_pixels) / float(total_pixels);
	}
}
/*
	check if (m_skin_filter != 0 && m_skin_filter->status() == 0) before call
*/
void AnnFaceDetect::skin_filter(char** r, char** g, char** b, const vec2Dc* search_mask)
{
	float ivec[3] = {0.0f, 0.0f, 0.0f};    //0.0 ... 1.0f range
	float ovec = 0.0f;

	m_skin_mask->set(0);

	unsigned int skin_pixels = 0;
	unsigned int total_pixels = 0;
	for (unsigned int y = get_dy(); y < m_skin_mask->height() - get_dy(); y++) {
		for (unsigned int x = get_dx(); x < m_skin_mask->width() - get_dx(); x++) {
			total_pixels++;

			if (search_mask != 0 && ((*search_mask)(y, x) == 0))				 
				continue;

			ivec[0] = (float)((int)r[y][x] + 128) / 255.0f;
			ivec[1] = (float)((int)g[y][x] + 128) / 255.0f;
			ivec[2] = (float)((int)b[y][x] + 128) / 255.0f;
			if (m_skin_filter->classify(ivec, &ovec) >= 0) {
				(*m_skin_mask)(y, x) = 1;
				skin_pixels++;
			}
		}
	}
	m_skin_amount = float(skin_pixels) / float(total_pixels);

	m_tmp_skin_mask->dilate(*m_skin_mask, 5, 5);
	m_skin_mask->erode(*m_tmp_skin_mask, 5, 5);
}

