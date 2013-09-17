// facedetect.cpp : Defines the initialization routines for the DLL.
//
#include "./ObjectLocator.h"

/////////////////////////////////////////////////////////////////////////////
// CFacedetectApp construction


static IplImage *big_image;
static IplImage *small_image;

ObjectLocator::ObjectLocator()
{
	int i,j;

	storage = NULL;
	cascade = NULL; 
	NoOfObjects=0;
	m_Scale = 1.3;

	for (i=0;i<MAXOBJECTCOUNT;i++)
	   for (j=0;j<4;j++)
		  object_location[i][j] = 0;

}

ObjectLocator::~ObjectLocator()
{	
	cvFree(&storage);
	cvFree(&cascade);
	UnInitImageStorage();
}



void ObjectLocator::SetScale(float scale)
{
	m_Scale=scale;
}

//csuimage to iplimage
void ObjectLocator::ManagedImagetoUnManagedImage(IplImage* Src)
{
	//use double buffering for higher frame rate
	//convert from csuImage to IplImage

	int i=0;

	for (int y=0;y<Src->height;y++)
	{
		for (int x=0;x<Src->width;x++)
		{	    
			//ARGB cahnnel
			big_image->imageData[i] = Src->imageData[i];
			i++;
		}
	}		
}

//resize and perform histogram equilization
void ObjectLocator::ImagePreProcessForFaceDetection()
{
	cvResize( big_image, small_image, CV_INTER_LINEAR );
    cvEqualizeHist( small_image, small_image );    
}

void ObjectLocator::UnInitImageStorage()
{
	if(small_image!=NULL) 
	{
		cvReleaseImage(&small_image);
		small_image = NULL;
	}

	if(big_image!=NULL) 
	{
		cvReleaseImage(&big_image);
		big_image = NULL;
	}
}

void ObjectLocator::InitImageStorage(int img_width, int img_height)
{
	UnInitImageStorage();
	
	int t1,t2;
	t1 = cvRound((img_width)/m_Scale);
	t2 = cvRound((img_height)/m_Scale);
	
	if(small_image==NULL)   small_image = cvCreateImage( cvSize(t1,t2), 8, 1 );
	if(big_image==NULL) 	big_image   = cvCreateImage( cvSize(img_width , img_height ), 8, 1 );
}

int ObjectLocator::InitObjectDetect(char* cascadename)
{
  int retval=1;

  if(storage==NULL) storage = cvCreateMemStorage();
  if(cascade==NULL) cascade = (CvHaarClassifierCascade*)cvLoad( cascadename, 0, 0, 0 );

  if( !cascade ) return false;
 
  return(retval);
}

bool ObjectLocator::GetObjectCoordinates(int oNum, int &tx, int &ty, int &bx, int &by,double scale)
{	
	if(oNum<NoOfObjects)
	{
		tx = (int)(object_location[oNum][0]*scale/m_Scale);
		ty = (int)(object_location[oNum][1]*scale/m_Scale);
		bx = (int)(object_location[oNum][2]*scale/m_Scale);
		by = (int)(object_location[oNum][3]*scale/m_Scale);
		return true;
	}
	else
	{
		tx=ty=bx=by=0;
	}
	return false;
}

bool ObjectLocator::GetObjectCoordinates(int oNum, int &tx, int &ty, int &bx, int &by)
{	
	if(oNum<NoOfObjects)
	{
		tx = object_location[oNum][0];
		ty = object_location[oNum][1];
		bx = object_location[oNum][2];
		by = object_location[oNum][3];
		return true;
	}
	else
	{
		tx=ty=bx=by=0;
	}
	return false;
}

void ObjectLocator::SetFaceROI(int index)
{
	CvRect rect;
	rect.x = ((object_location[index][0]/m_Scale)-20)>0?(int)((object_location[index][0]/m_Scale)-20):0;
	rect.y = ((object_location[index][1]/m_Scale)-20)>0?(int)((object_location[index][1]/m_Scale)-20):0;
	rect.width = ((object_location[index][2]/m_Scale)+20)>0?(int)((object_location[index][2]/m_Scale)+20):small_image->width;
	rect.height = ((object_location[index][3]/m_Scale)+20)>0?(int)((object_location[index][3]/m_Scale)+20):small_image->height;

	cvSetImageROI(small_image, rect); 	
}

void ObjectLocator::UnSetFaceROI()
{
	small_image->roi = NULL;
}

int ObjectLocator::DetectObjects()
{    
	int i;
    cvClearMemStorage( storage );	
	
	NoOfObjects = 0;
    if( cascade )
    {
        //double t = (double)cvGetTickCount();
        CvSeq* objects = cvHaarDetectObjects( small_image, cascade, storage,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
        //t = (double)cvGetTickCount() - t;
        //printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
		
		NoOfObjects = objects->total;
		
		//CvRect r;
        for( i = 0; i < (objects ? objects->total : 0); i++ )
        {	
			if (i<MAXOBJECTCOUNT)
			{
				CvRect* r = (CvRect*)cvGetSeqElem( objects, i );
				
				//out put these :)
				object_location[i][0] = (int)(r->x*m_Scale);
				object_location[i][1] = (int)(r->y*m_Scale);
				object_location[i][2] = (int)(r->width*m_Scale);
				object_location[i][3] = (int)(r->height*m_Scale);
			}		  
		}
		//cvFree(&r);
		//cvFree(&objects);
    }

  
	return (NoOfObjects>MAXOBJECTCOUNT)?MAXOBJECTCOUNT:NoOfObjects;
}

