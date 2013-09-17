
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>

#include "vec2d.h"


/////////////////////////constructors/destructors////////////////////////////////////////////////////
vec2D::vec2D(unsigned int ysize, unsigned int xsize,
	     int yoffset, int xoffset, const float* data) : m_width(xsize), m_height(ysize),
		m_xoffset(xoffset), m_yoffset(yoffset), m_data(0)
{
	init(ysize, xsize, yoffset, xoffset);

	const float* pdata = data;
	for (int y = yfirst(); y <= ylast(); y++) {
		for (int x = xfirst(); x <= xlast() ; x++) {
			if (data != 0)
				m_data[y][x] = *pdata++;
			else
				m_data[y][x] = 0.0f;
		}
	}
}
vec2D::vec2D(const vec2D& v)
{
	init(v.height(), v.width(), v.yfirst(), v.xfirst());
	init(v);
}
vec2D::vec2D(const wchar_t* file) : m_width(0), m_height(0), m_xlast(0), m_ylast(0),
		m_xoffset(0), m_yoffset(0), m_data(0)
{
	float val;

	FILE* fp = _wfopen(file, L"rt");
	if (fp) {
		if (fwscanf(fp, L"%d %d", &m_height, &m_width) != 2) {
			fclose(fp);
			init(1, 1);
			return;
		}

		init(m_height, m_width);

		for (int y = yfirst(); y <= ylast(); y++) {
			for (int x = xfirst(); x <= xlast() ; x++) {
				if (fwscanf(fp, L"%f", &val) != 1) {
					m_data[y][x] = 0.0f;
				} else
					m_data[y][x] = val;
			}
		}

		fclose(fp);
	} else
		init(1, 1);
}
vec2D::~vec2D()
{
	if (m_data != 0)
		close();
}
////////////////////////////////////////////////////////////////////////////////





//////////////////////init,free memory//////////////////////////////////////////
void vec2D::init(unsigned int ysize, unsigned int xsize, int yoffset, int xoffset)
{
	m_width = xsize;
	m_height = ysize;
	m_xoffset = xoffset;
	m_yoffset = yoffset;

	m_xlast = (m_width + m_xoffset) - 1;
	m_ylast = (m_height + m_yoffset) - 1;

	m_data = (float**) malloc(m_height * sizeof(float*));	 //setup rows
	for (unsigned int j = 0; j < m_height; j++) {
		m_data[j] = (float*) _aligned_malloc(m_width * sizeof(float), 16);       //setup cols
		m_data[j] -= m_xoffset;
	}
	m_data -= m_yoffset;
}
void vec2D::init(const vec2D& v)
{
	for (int y = v.yfirst(); y <= v.ylast(); y++)
		for (int x = v.xfirst(); x <= v.xlast(); x++)
			(*this)(y, x) = v(y, x);
}
void vec2D::close(void)
{
	m_data += m_yoffset;
	for (unsigned int j = 0; j < m_height; j++)
		_aligned_free(m_data[j] + m_xoffset);      //delete colums
	free(m_data);       //delete rows

	m_data = 0;
	m_width = 0;
	m_height = 0;
}
void vec2D::print(const wchar_t* file) const
{
	const vec2D &v = *this;
	if (file) {
		FILE *fp = _wfopen(file, L"wt");
		if (fp) {
			fwprintf(fp, L"\n vec: %p\n", this);
			for (int y = v.yfirst(); y <= v.ylast(); y++) {
				for (int x = v.xfirst(); x <= v.xlast(); x++)
					fwprintf(fp, L" %g", v(y, x));
				fwprintf(fp, L"\n");
			}
			fclose(fp);
		}
	} else {
		wprintf(L"\n vec: %p\n", this);
		for (int y = v.yfirst(); y <= v.ylast(); y++) {
			for (int x = v.xfirst(); x <= v.xlast(); x++)
				wprintf(L" %g", v(y, x));
			wprintf(L"\n");
		}
	}
}
////////////////////////////////////////////////////////////////////////////////






/////////////////////operators//////////////////////////////////////////////////
void vec2D::set(float scalar)
{
	vec2D &v = *this;
	for (int y = v.yfirst(); y <= v.ylast(); y++)
		for (int x = v.xfirst(); x <= v.xlast(); x++)
			v(y, x) = scalar;
}
//set to Rect [ left, right )
//	    [ top, bottom )
void vec2D::set(float scalar, RECT& r)			      //0-offset array function
{
	vec2D &v = *this;

	if (v.xfirst() != 0 || v.yfirst() != 0)
		return;

	if (r.top < 0) r.top = 0;
	if (r.left < 0) r.left = 0;
	if ((unsigned int)r.bottom > v.height()) r.bottom = v.height();
	if ((unsigned int)r.right > v.width()) r.right = v.width();

	__m128 mscalar = _mm_load_ps1(&scalar);
	unsigned int width = r.right - r.left;

	for (unsigned int y = (unsigned int)r.top; y < (unsigned int)r.bottom; y++) {
		for (unsigned int x = 0; x < width / 4; x++)
			_mm_storeu_ps(&v(y, r.left + 4*x), mscalar);      //store unaligned r.left%4 might be nonzero

		if (width % 4) {
			for (unsigned int x = width - width % 4; x < width; x++)
				v(y, r.left + x) = scalar;
		}
	}
}
void vec2D::setrand()
{
	vec2D &v = *this;

	int r;
	srand((unsigned int)time(0));
	for (int y = v.yfirst(); y <= v.ylast(); y++) {
		for (int x = v.xfirst(); x <= v.xlast(); x++) {
			r = 0xFFF & rand();
			r -= 0x800;
			v(y, x) = (float)r / 2048.0f;
		}
	}
}

bool vec2D::copy(const vec2D& v, int left, int top)					//copy [hxw] region from top,left offset A to this
{
	//0-offset array function
	//v size >= this size !
	vec2D& pv = *this;
	if ((v.xfirst() || v.yfirst()) || (pv.xfirst() || pv.yfirst()))
		return false;

	RECT r;			   //selected rectangle
	r.left = left;		    //left,top coords
	r.top = top;
	r.right = r.left + width();       //right,bottom coords
	r.bottom = r.top + height();

	if ((r.left >= 0 && r.top >= 0) && (r.right <= (int)v.width() && r.bottom <= (int)v.height())) {       //operator()
		for (unsigned int y = 0; y < height(); y++)
			for (unsigned int x = 0; x < width(); x++)
				pv(y, x) = v(y + r.top, x + r.left);
	} else { //get
		for (unsigned int y = 0; y < height(); y++)
			for (unsigned int x = 0; x < width(); x++)
				pv(y, x) = v.get(y + r.top, x + r.left);
	}

	return true;
}
/////////////////////////////////////////////////////////////////////////////////



///////zero offset operations////////////////////////////////////////////////////
void vec2D::add(const vec2D& a, const vec2D& b)      //this = a.+b
{
	vec2D& c = *this;

	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_add_ps(_mm_load_ps(a.data(y, 4*x)), _mm_load_ps(b.data(y, 4*x))));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) = a(y, x) + b(y, x);
		}
	}
}
void vec2D::sub(const vec2D& a, const vec2D& b)      //this = a.-b
{
	vec2D& c = *this;
	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_sub_ps(_mm_load_ps(a.data(y, 4*x)), _mm_load_ps(b.data(y, 4*x))));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) = a(y, x) - b(y, x);
		}
	}
}
void vec2D::mule(const vec2D& a, const vec2D& b)      //this = a.*b
{
	vec2D& c = *this;
	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_mul_ps(_mm_load_ps(a.data(y, 4*x)), _mm_load_ps(b.data(y, 4*x))));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) = a(y, x) * b(y, x);
		}
	}
}
void vec2D::mul(const vec2D& a, const vec2D& b)      //this = a*b
{
	vec2D& c = *this;
	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width(); x++) {
			c(y, x) = 0.0f;
			for (unsigned int i = 0; i < a.width(); i++)
				c(y, x) += a(y, i) * b(i, x);
		}
	}
}
void vec2D::mult(const vec2D& a, const vec2D& b)      //this = a*b'
{
	vec2D& c = *this;
	for (unsigned int y = 0; y < c.height(); y++)
		for (unsigned int x = 0; x < c.width(); x++)
			c(y, x) = mconv(a.data(y, 0), b.data(x, 0), a.width());
}
void vec2D::div(const vec2D& a, const vec2D& b)      //this = a./b
{
	vec2D& c = *this;
	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_div_ps(_mm_load_ps(a.data(y, 4*x)), _mm_load_ps(b.data(y, 4*x))));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) = a(y, x) / b(y, x);
		}
	}
}

void vec2D::add(float scalar)	   //this = this.+scalar   sse optimized
{
	vec2D& c = *this;
	__m128 mscalar = _mm_load_ps1(&scalar);

	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_add_ps(_mm_load_ps(&c(y, 4*x)), mscalar));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) += scalar;
		}
	}
}
void vec2D::sub(float scalar)	   //this = this.-scalar   sse optimized
{
	vec2D& c = *this;
	__m128 mscalar = _mm_load_ps1(&scalar);

	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_sub_ps(_mm_load_ps(&c(y, 4*x)), mscalar));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) -= scalar;
		}
	}
}
void vec2D::mul(float scalar)	   //this = this.*scalar   sse optimized
{
	vec2D& c = *this;
	__m128 mscalar = _mm_load_ps1(&scalar);

	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_mul_ps(_mm_load_ps(&c(y, 4*x)), mscalar));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) *= scalar;
		}
	}
}
void vec2D::div(float scalar)	   //this = this./scalar   sse optimized
{
	vec2D& c = *this;
	__m128 mscalar = _mm_load_ps1(&scalar);

	for (unsigned int y = 0; y < c.height(); y++) {
		for (unsigned int x = 0; x < c.width() / 4; x++)
			_mm_store_ps(&c(y, 4*x), _mm_div_ps(_mm_load_ps(&c(y, 4*x)), mscalar));

		if ((c.width() % 4) != 0) {
			for (unsigned int x = c.width() - c.width() % 4; x < c.width(); x++)
				c(y, x) /= scalar;
		}
	}
}
float vec2D::prod() const
{
	const vec2D& c = *this;

	float fres = 1.0f;
	__declspec(align(16)) float tmp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	__m128 mres;

	for (unsigned int y = 0; y < height(); y++) {
		for (unsigned int x = 0; x < width() / 4; x++) {
			if (y == 0)
				mres = _mm_load_ps(c.data(0, 0));
			else
				mres = _mm_mul_ps(mres, _mm_load_ps(c.data(y, 4 * x)));
		}

		if ((width() % 4) != 0) {
			for (unsigned int x = width() - width() % 4; x < width(); x++)
				fres *= c(y, x);
		}
	}

	//mres: a,b,c,d
	__m128 m = _mm_movehl_ps(mres, mres);    //m:  c,d,c,d
	mres = _mm_mul_ps(m, mres);	      //mres: a*c,b*d,*,*
	_mm_store_ps(tmp, mres);

	return tmp[0] * tmp[1] * fres;
}

void vec2D::inter2(const vec2D& src, vec2D& dst_grdx, vec2D& dst_grdy)		//2d interpolation
{
	vec2D& trg = *this;

	float xrto = float(width() - 1) / float(src.width() - 1);       //trg/src
	float yrto = float(height() - 1) / float(src.height() - 1);

	//arrange before srcx,srcy,frcx,frcy to speed calcs
	for (unsigned int y = 0; y < height(); y++) {
		float srcy = (float)y / yrto;
		float frcy = srcy - float((int)srcy);
		dst_grdy(0, y) = srcy;
		dst_grdy(1, y) = frcy;
	}

	for (unsigned int x = 0; x < width(); x++) {
		float srcx = (float)x / xrto;	       //position to take from src vec2D
		float frcx = srcx - float((int)srcx);       //srcx=1.34  frcx=.34
		dst_grdx(0, x) = srcx;
		dst_grdx(1, x) = frcx;
	}
	//arrange before srcx,srcy,frcx,frcy to speed calcs

	for (unsigned int y = 0; y < height(); y++) {
		for (unsigned int x = 0; x < width(); x++) {

			unsigned int sx = (unsigned int)dst_grdx(0, x);	 //x index to source
			unsigned int sy = (unsigned int)dst_grdy(0, y);	 //y index to source
			trg(y, x) = src(sy, sx) * (1.0f - dst_grdy(1, y)) * (1.0f - dst_grdx(1, x));	//1-frcy 1-frcx

			if (dst_grdx(1, x) > 0.0f && sx + 1 < src.width())
				trg(y, x) += src(sy, sx + 1) * (1.0f - dst_grdy(1, y)) * dst_grdx(1, x);	//1-frcy frcx
			if (dst_grdy(1, y) > 0.0f && sy + 1 < src.height())
				trg(y, x) += src(sy + 1, sx) * dst_grdy(1, y) * (1.0f - dst_grdx(1, x));	//frcy 1-frcx
			if ((dst_grdx(1, x) > 0.0f && dst_grdy(1, y) > 0.0f) && (sx + 1 < src.width() && sy + 1 < src.height()))
				trg(y, x) += src(sy + 1, sx + 1) * dst_grdy(1, y) * dst_grdx(1, x);	    //frcy frcx
		}
	}
}
///////zero offset operations////////////////////////////////////////////////////





///////////////////mat operations///////////////////////////////////////////////
void vec2D::conv2D(const vec2D& a, const vec2D& filter)	//this = conv2D(A, filter)  (this = A in sizes)
{
	vec2D& c = *this;
	for (int y = c.yfirst(); y <= c.ylast(); y++) {
		for (int x = c.xfirst(); x <= c.xlast(); x++) {

			c(y, x) = 0.0f;
			for (int n = filter.yfirst(); n <= filter.ylast(); n++)
				for (int m = filter.xfirst(); m <= filter.xlast(); m++)
					c(y, x) += filter(n, m) * a.get(y + n, x + m);
		}
	}
}
void vec2D::conv2D(const vec2D& a, const vec2D& re, const vec2D& im)	//this = conv2D(A, Im,Re)  (this = A in sizes)
{
	vec2D& c = *this;
	for (int y = c.yfirst(); y <= c.ylast(); y++) {
		for (int x = c.xfirst(); x <= c.xlast(); x++) {

			float imag = 0.0f;
			float real = 0.0f, tmp;
			for (int n = re.yfirst(); n <= re.ylast(); n++) {
				for (int m = re.xfirst(); m <= re.xlast(); m++) {
					tmp = a.get(y + n, x + m);
					real += re(n, m) * tmp;
					imag += im(n, m) * tmp;
				}
			}
			c(y, x) = sqrt(real * real + imag * imag);  //abs value
		}
	}
}
void vec2D::minmax(float& min, float& max) const
{
	const vec2D& c = *this;

	min = c(yfirst(), xfirst());
	max = min;

	for (int y = c.yfirst(); y <= c.ylast(); y++) {
		for (int x = c.xfirst(); x <= c.xlast(); x++) {
			if (c(y, x) < min) min = c(y, x);
			if (c(y, x) > max) max = c(y, x);
		}
	}
}
float vec2D::minval() const
{
	const vec2D& c = *this;

	float min = c(yfirst(), xfirst());

	for (int y = c.yfirst(); y <= c.ylast(); y++) {
		for (int x = c.xfirst(); x <= c.xlast(); x++) {
			if (c(y, x) < min) min = c(y, x);
		}
	}

	return min;
}
float vec2D::maxval() const
{
	const vec2D& c = *this;

	float max = c(yfirst(), xfirst());

	for (int y = c.yfirst(); y <= c.ylast(); y++) {
		for (int x = c.xfirst(); x <= c.xlast(); x++) {
			if (c(y, x) > max) max = c(y, x);
		}
	}

	return max;
}

//get max value with [x,y] coord from offset dx,dy in rect [sizex,sizey]
void vec2D::maxval(float& max, int& x, int& y, int sizex, int sizey, int dx, int dy) const
{
	const vec2D& c = *this;

	max = -FLT_MAX;

	if (dx == 0 || dx < (sizex - 1) / 2)
		dx = (sizex - 1) / 2;
	if (dy == 0 || dy < (sizey - 1) / 2)
		dy = (sizey - 1) / 2;

	x = dx;
	y = dy;

	float tmp = 0.0f;
	for (unsigned int n = dy; n < height() - dy; n++) {
		for (unsigned int m = dx; m < width() - dx; m++) {

			tmp = 0.0f;
			for (int i = -(sizey - 1) / 2; i <= (sizey - 1) / 2; i++)
				for (int j = -(sizex - 1) / 2; j <= (sizex - 1) / 2; j++)
					tmp += c(n + i, m + j);

			if (tmp > max) {
				max = tmp;
				y = n;
				x = m;
			}
		}
	}
}

void vec2D::normalize(float a, float b)
{
	vec2D& c = *this;

	float min, max;
	minmax(min, max);

	c.sub(min);
	c.mul((b - a) / (max - min));
	c.add(a);
}
void vec2D::histeq(vec2D &hist)    //hist 1x256 array
{
	vec2D& c = *this;

	hist.set(0.0f);

	for (int y = c.yfirst(); y <= c.ylast(); y++)
		for (int x = c.xfirst(); x <= c.xlast(); x++)
			hist(0, int(c(y, x)))++;

	for (unsigned int x = 1; x < hist.width(); x++)
		hist((unsigned)0, x) += hist((unsigned)0, x - 1);

	hist.div(float(width() * height()));

	for (int y = c.yfirst(); y <= c.ylast(); y++)
		for (int x = c.xfirst(); x <= c.xlast(); x++)
			c(y, x) = (float) hist(0, int(c(y, x)));
}
void vec2D::fliplr()
{
	vec2D& c = *this;
	float tmp;

	for (unsigned int i = 0; i < width() / 2; i++) {
		for (int y = yfirst(); y <= ylast(); y++) {
			tmp = c(y, xfirst() + i);
			c(y, xfirst() + i) = c(y, xlast() - i);
			c(y, xlast() - i) = tmp;
		}
	}
}
