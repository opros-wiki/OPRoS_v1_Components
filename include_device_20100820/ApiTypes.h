#ifndef	_API_TYPES_H_
#define	_API_TYPES_H_

#include <boost/serialization/split_member.hpp>
#include <boost/operators.hpp>
#include <vector>
#include <valarray>
#include <deque>
#include "OprosMath.h"
#include "../../../../CommonLibrary/OpenCV/OpenCV2.1_Windows/include/opencv/cv.h"

using namespace std;

class ObjectLocation : public boost::operators<ObjectLocation>
{
public:
	double x, y, theta;

public:
	friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & x & y & theta;
    }

public:
	ObjectLocation () { }
	ObjectLocation (double len, double th_) : x (len * cos (th_)), y (len * sin (th_)), theta (th_) { }
	ObjectLocation (double x_, double y_, double th_) : x (x_), y (y_), theta (th_) { }

public: 
	ObjectLocation & operator += (const ObjectLocation &p) { x += p.x; y += p.y; theta += p.theta; return *this; }
	ObjectLocation & operator -= (const ObjectLocation &p) { x -= p.x; y -= p.y; theta -= p.theta; return *this; }
	ObjectLocation & operator *= (const ObjectLocation &p) { x *= p.x; y *= p.y; theta *= p.theta; return *this; }
	ObjectLocation & operator /= (const ObjectLocation &p) { x /= p.x; y /= p.y; theta /= p.theta; return *this; }
	ObjectLocation & operator *= (double d)                { x *= d;   y *= d;   theta *= d;    return *this; }

	ObjectLocation &Rotate (double rad)
	{
		double c = cos (rad);
		double s = sin (rad);
		double x_ = x * c - y * s;
		double y_ = x * s + y * c;
		x = x_;
		y = y_;
		theta += rad;
		return *this;
	}

	ObjectLocation &Translate (double x_, double y_)
	{
		x += x_;
		y += y_;
		return *this;
	}

	ObjectLocation &Transform (const ObjectLocation &p)
	{
		Rotate (p.theta);
		Translate (p.x, p.y);
		return *this;
	}

	double Atan ()   { return atan2 (y, x); }
	double Length () { return sqrt (x*x + y*y); }
	double Distance (ObjectLocation &p) { double dx = p.x - x, dy = p.y - y; return sqrt (dx * dx + dy * dy); }
};
inline ObjectLocation diff (const ObjectLocation &v1, const ObjectLocation &v2) { return ObjectLocation (v1.x - v2.x, v1.y - v2.y, DeltaRad (v1.theta, v2.theta)); }

class ObjectPosition
{
public:
	ObjectPosition() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
		roll = 0.0;
		pitch = 0.0;
		yaw = 0.0;
	}
	ObjectPosition(double x, double y, double z, double roll, double pitch, double yaw) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->roll = roll;
		this->pitch = pitch;
		this->yaw = yaw;
	}
	virtual ~ObjectPosition() { };
	friend class boost::serialization::access;

	double x;
	double y;
	double z;
	double roll;
	double pitch;
	double yaw;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & x & y & z & roll & pitch & yaw;
	}

	ObjectPosition operator=(const ObjectPosition &objectPosition)
	{
		this->x = objectPosition.x;
		this->y = objectPosition.y;
		this->z = objectPosition.z;
		this->roll = objectPosition.roll;
		this->pitch = objectPosition.pitch;
		this->yaw = objectPosition.yaw;

		return *this;
	}

	ObjectPosition operator+(const ObjectPosition &objectPosition)
	{
		this->x += objectPosition.x;
		this->y += objectPosition.y;
		this->z += objectPosition.z;
		this->roll += objectPosition.roll;
		this->pitch += objectPosition.pitch;
		this->yaw += objectPosition.yaw;

		return *this;
	}

	ObjectPosition operator-(const ObjectPosition &objectPosition)
	{
		this->x -= objectPosition.x;
		this->y -= objectPosition.y;
		this->z -= objectPosition.z;
		this->roll -= objectPosition.roll;
		this->pitch -= objectPosition.pitch;
		this->yaw -= objectPosition.yaw;

		return *this;
	}

	ObjectPosition operator*(const ObjectPosition &objectPosition)
	{
		this->x *= objectPosition.x;
		this->y *= objectPosition.y;
		this->z *= objectPosition.z;
		this->roll *= objectPosition.roll;
		this->pitch *= objectPosition.pitch;
		this->yaw *= objectPosition.yaw;

		return *this;
	}

	ObjectPosition operator/(const ObjectPosition &objectPosition)
	{
		this->x /= objectPosition.x;
		this->y /= objectPosition.y;
		this->z /= objectPosition.z;
		this->roll /= objectPosition.roll;
		this->pitch /= objectPosition.pitch;
		this->yaw /= objectPosition.yaw;

		return *this;
	}
};

class ObjectPosture
{
public:
    friend class boost::serialization::access;
    
    double pRate;
    double qRate;
    double rRate;
    double xAcceleration;
    double yAcceleration;
    double zAcceleration;
    double roll;
    double pitch;
    double yaw;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & pRate & qRate & rRate & xAcceleration & yAcceleration & zAcceleration & roll & pitch & yaw;
    }
    
    ObjectPosture operator=(const ObjectPosture &objectPosture)
    {
        this->pRate = objectPosture.pRate;
        this->qRate = objectPosture.qRate;
        this->rRate = objectPosture.rRate;
        this->xAcceleration = objectPosture.xAcceleration;
        this->yAcceleration = objectPosture.yAcceleration;
        this->zAcceleration = objectPosture.zAcceleration;
        this->roll = objectPosture.roll;
        this->pitch = objectPosture.pitch;
        this->yaw = objectPosture.yaw;
        
        return *this;
    }
    
    ObjectPosture operator+(const ObjectPosture &objectPosture)
    {
        this->pRate += objectPosture.pRate;
        this->qRate += objectPosture.qRate;
        this->rRate += objectPosture.rRate;
        this->xAcceleration += objectPosture.xAcceleration;
        this->yAcceleration += objectPosture.yAcceleration;
        this->zAcceleration += objectPosture.zAcceleration;
        this->roll += objectPosture.roll;
        this->pitch += objectPosture.pitch;
        this->yaw += objectPosture.yaw;
        
        return *this;
    }
    
    ObjectPosture operator-(const ObjectPosture &objectPosture)
    {
        this->pRate -= objectPosture.pRate;
        this->qRate -= objectPosture.qRate;
        this->rRate -= objectPosture.rRate;
        this->xAcceleration -= objectPosture.xAcceleration;
        this->yAcceleration -= objectPosture.yAcceleration;
        this->zAcceleration -= objectPosture.zAcceleration;
        this->roll -= objectPosture.roll;
        this->pitch -= objectPosture.pitch;
        this->yaw -= objectPosture.yaw;
        
        return *this;
    }
    
    ObjectPosture operator*(const ObjectPosture &objectPosture)
    {
        this->pRate *= objectPosture.pRate;
        this->qRate *= objectPosture.qRate;
        this->rRate *= objectPosture.rRate;
        this->xAcceleration *= objectPosture.xAcceleration;
        this->yAcceleration *= objectPosture.yAcceleration;
        this->zAcceleration *= objectPosture.zAcceleration;
        this->roll *= objectPosture.roll;
        this->pitch *= objectPosture.pitch;
        this->yaw *= objectPosture.yaw;
        
        return *this;
    }
    
    ObjectPosture operator/(const ObjectPosture &objectPosture)
    {
        this->pRate /= objectPosture.pRate;
        this->qRate /= objectPosture.qRate;
        this->rRate /= objectPosture.rRate;
        this->xAcceleration /= objectPosture.xAcceleration;
        this->yAcceleration /= objectPosture.yAcceleration;
        this->zAcceleration /= objectPosture.zAcceleration;
        this->roll /= objectPosture.roll;
        this->pitch /= objectPosture.pitch;
        this->yaw /= objectPosture.yaw;
        
        return *this;
    }
};

/*

class DHParameter
{
public:
	friend class boost::serialization::access;

	enum _JOINT_TYPE
	{
		FIXED_JOINT,
		REVOLUTE_JOINT,
		PRISMATIC_JOINT
	};

	double a;
	double b;
	double alpha;
	double d;
	double theta;
	int direction;
	bool isVirtual;
	int jointType;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & a & b & alpha & d & theta & direction & isVirtual & jointType;
	}

	DHParameter operator=(const DHParameter &dhParameter)
	{
		this->a = dhParameter.a;
		this->b = dhParameter.b;
		this->alpha = dhParameter.alpha;
		this->d = dhParameter.d;
		this->theta = dhParameter.theta;
		this->direction = dhParameter.direction;
		this->isVirtual = dhParameter.isVirtual;
		this->jointType = dhParameter.jointType;

		return *this;
	}
};

class ManipulatorParameter
{
public:
	friend class boost::serialization::access;

	int size;										//dh의 사이즈
	std::vector<int>	id;
	std::vector<DHParameter> dhParameter;
	std::vector< std::valarray<double> > axisPosition;		//reference frame기준 joint frame의 원점 좌표(x,y,z)
	std::vector< std::valarray<double> > axisZ;			//joint frame z-axis(0,0,1)의 reference frame 에 대한 성분(directional cosine)
	std::vector<double> maximumVelocity;
	std::vector<double> acceleration;
	std::vector<double> minimumRange;
	std::vector<double> maximumRange;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & size & id & dhParameter & axisPosition & axisZ & maximumVelocity & acceleration & minimumRange & maximumRange;
	}

	ManipulatorParameter operator=(const ManipulatorParameter &ManipulatorParameter)
	{
		this->size = ManipulatorParameter.size;
		this->id = ManipulatorParameter.id;
		this->dhParameter = ManipulatorParameter.dhParameter;
		this->axisPosition = ManipulatorParameter.axisPosition;
		this->axisZ = ManipulatorParameter.axisZ;
		this->maximumVelocity = ManipulatorParameter.maximumVelocity;
		this->acceleration = ManipulatorParameter.acceleration;
		this->minimumRange = ManipulatorParameter.minimumRange;
		this->maximumRange = ManipulatorParameter.maximumRange;

		return *this;
	}
};
*/

class WheelControlVelocity
{
public:
	WheelControlVelocity() { forward = 0.0;	angular = 0.0; }
	friend class boost::serialization::access;

	double forward;
	double angular;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & forward & angular;
	}

	WheelControlVelocity operator=(const WheelControlVelocity &mobilityVelocity)
	{
		this->forward = mobilityVelocity.forward;
		this->angular = mobilityVelocity.angular;

		return *this;
	}
};


class VisionRecognitionResult
{
public:
    friend class boost::serialization::access;
    
	std::string name;
	int point1X;
	int point1Y;
	int point2X;
	int point2Y;
	int point3X;
	int point3Y;
	int point4X;
	int point4Y;

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & name, point1X, point1Y, point2X, point2Y, point3X, point3Y, point4X, point4Y;
    }
    
	VisionRecognitionResult operator=(const VisionRecognitionResult &visionRecognitionResult)
	{
		this->name = visionRecognitionResult.name;
		this->point1X = visionRecognitionResult.point1X;
		this->point1Y = visionRecognitionResult.point1Y;
		this->point2X = visionRecognitionResult.point2X;
		this->point2Y = visionRecognitionResult.point2Y;
		this->point3X = visionRecognitionResult.point3X;
		this->point3Y = visionRecognitionResult.point3Y;
		this->point4X = visionRecognitionResult.point4X;
		this->point4Y = visionRecognitionResult.point4Y;
		
		return *this;
	}
};

class ColorRange
{
public:
	std::string name;
	unsigned char	min1;
	unsigned char	max1;
	unsigned char	min2;
	unsigned char	max2;
	unsigned char	min3;
	unsigned char	max3;

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & name, min1, max1, min2, max2, min3, max3;
    }
    
	ColorRange operator=(const ColorRange &colorRange)
	{
		this->name = colorRange.name;
		this->min1 = colorRange.min1;
		this->max1 = colorRange.max1;
		this->min2 = colorRange.min2;
		this->max2 = colorRange.max2;
		this->min3 = colorRange.min3;
		this->max3 = colorRange.max3;
		
		return *this;
	}
};

class CANObject
{
public:
	CANObject(void)
	{
	}
	virtual ~CANObject(void) { }

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & id & data;
    }
    
	CANObject operator=(const CANObject &canObject)
	{
		this->id = canObject.id;
		this->data = canObject.data;
						
		return *this;
	}

	long id;
	vector<unsigned char> data;
};

class JoystickData
{
public:
	JoystickData(void)
	{
	}
	virtual ~JoystickData(void) { }

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & x & y & z & button;
    }
    
	JoystickData operator=(const JoystickData &joystickData)
	{
		this->x = joystickData.x;
		this->y = joystickData.y;
		this->z = joystickData.z;
		this->button = joystickData.button;
						
		return *this;
	}

	double x;
	double y;
	double z;
	vector<bool> button;
};

class GPSData
{
public:
	GPSData(void)
	{
	}
	virtual ~GPSData(void) { }

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & latitude & longitude & time & velocity;
    }
    
	GPSData operator=(const GPSData &gpsData)
	{
		this->latitude = gpsData.latitude;
		this->longitude = gpsData.longitude;
		this->time = gpsData.time;
		this->velocity = gpsData.velocity;
						
		return *this;
	}

	double latitude;
	double longitude;
	string time;
	double velocity;
};

class Point3D
{
public:
	friend class boost::serialization::access;

	double x;
	double y;
	double z;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & x & y & z;
	}

	Point3D operator=(const Point3D &point)
	{
		this->x = point.x;
		this->y = point.y;
		this->z = point.z;

		return *this;
	}

	Point3D operator+(const Point3D &point)
	{
		this->x += point.x;
		this->y += point.y;
		this->z += point.z;

		return *this;
	}

	Point3D operator-(const Point3D &point)
	{
		this->x -= point.x;
		this->y -= point.y;
		this->z -= point.z;

		return *this;
	}

	Point3D operator*(const Point3D &point)
	{
		this->x *= point.x;
		this->y *= point.y;
		this->z *= point.z;

		return *this;
	}

	Point3D operator/(const Point3D &point)
	{
		this->x /= point.x;
		this->y /= point.y;
		this->z /= point.z;

		return *this;
	}
};

class Triangle3D
{
public:
	friend class boost::serialization::access;

	Point3D pos1;
	Point3D pos2;
	Point3D pos3;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & pos1 & pos2 & pos3;
	}

	Triangle3D operator=(const Triangle3D &triangle)
	{
		this->pos1 = triangle.pos1;
		this->pos2 = triangle.pos2;
		this->pos3 = triangle.pos3;

		return *this;
	}

};


class Obstacle3D
{
public:
	friend class boost::serialization::access;

	std::string name;
	std::vector<Triangle3D> surface;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & name & surface;
	}

	Obstacle3D operator=(const Obstacle3D &obs)
	{
		this->surface = obs.surface;
		this->name = obs.name;
		return *this;
	}

};

class Hexahedron3D
{
public:
	friend class boost::serialization::access;

protected:
	Point3D Ver[8];	

	// 꼭지점 위치
	//                        7-----6
	//                       /I     I
	//                      / I     I 
	//                     /  4-----5
	//                    /  /	   /				
	//        Y   Z      3--/--2  /
	//        I  /       I /   I /
	//        I /        I/    I/
	//        I/___X     0-----1

public:
	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & Ver;
	}
};
class RectSolid3D : public Hexahedron3D
{
public:
	friend class boost::serialization::access;

	// 꼭지점 위치
	//                        7-----6
	//                       /I     I
	//                      / I     I 
	//                     /  4-----5
	//                    /  /	   /				
	//        Y   Z      3--/--2  /
	//        I  /       I /   I /
	//        I /        I/    I/
	//        I/___X     0-----1


	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & Ver;
	}

	RectSolid3D operator+(const RectSolid3D &hexa)
	{
		for(int i=0; i<8 ; i++) this->Ver[i] = hexa.Ver[i];
		return *this;
	}


	void setRectSolid(Point3D origin_point, double width, double length, double height)
	{
		Ver[0].x = origin_point.x - abs(width*0.5);
		Ver[0].y = origin_point.y - abs(length*0.5);
		Ver[0].z = origin_point.z;
		Ver[1].x = origin_point.x + abs(width*0.5);
		Ver[1].y = origin_point.y - abs(length*0.5);
		Ver[1].z = origin_point.z;
		Ver[2].x = origin_point.x + abs(width*0.5);
		Ver[2].y = origin_point.y + abs(length*0.5);
		Ver[2].z = origin_point.z;
		Ver[3].x = origin_point.x - abs(width*0.5);
		Ver[3].y = origin_point.y + abs(length*0.5);
		Ver[3].z = origin_point.z;
		Ver[4].x = origin_point.x - abs(width*0.5);
		Ver[4].y = origin_point.y - abs(length*0.5);
		Ver[4].z = origin_point.z + abs(height);
		Ver[5].x = origin_point.x + abs(width*0.5);
		Ver[5].y = origin_point.y - abs(length*0.5);
		Ver[5].z = origin_point.z + abs(height);
		Ver[6].x = origin_point.x + abs(width*0.5);
		Ver[6].y = origin_point.y + abs(length*0.5);
		Ver[6].z = origin_point.z + abs(height);
		Ver[7].x = origin_point.x - abs(width*0.5);
		Ver[7].y = origin_point.y + abs(length*0.5);
		Ver[7].z = origin_point.z + abs(height);

	}
	void setRectSolid2Corner(Point3D one_corner, Point3D two_corner )
	{
		Point3D origin;

		double height = abs(one_corner.z - two_corner.z);
		if(one_corner.z < two_corner.z)
			origin.z = one_corner.z;
		else
			origin.z = two_corner.z;

		double width = abs(one_corner.x - two_corner.x);
		origin.x = 0.5*(one_corner.x + two_corner.x);
		double length = abs(one_corner.y - two_corner.y);
		origin.y = 0.5*(one_corner.y + two_corner.y);

		setRectSolid(origin, width, length, height);
	}
	//점이 직사각형에 포함되면 true 
	bool includecheck_point(Point3D P)
	{
		int out = 0;
		//x영역검사
		if( P.x < Ver[0].x || Ver[1].x < P.x)
			out++;	
		//y영역검사
		if( P.y < Ver[0].y || Ver[3].y < P.y)
			out++;
		//z영역검사
		if( P.z < Ver[0].z || Ver[4].z < P.z)
			out++;
		if(out == 0)
			return true;
		else
			return false;
	}

	//삼각형이 직사각형에 포함되면 true 
	bool includecheck_triangle(Triangle3D T)
	{
		int out =0;
		if( false == includecheck_point(T.pos1) )
			out++;
		if( false == includecheck_point(T.pos2) )
			out++;
		if( false == includecheck_point(T.pos3) )
			out++;

		if(out == 0)
			return true;
		else
			return false;
	}
	std::vector<Triangle3D> get_triangleset(void)	//직육면체를 표현하는 삼각형 배열을 출력한다.삼각형은 오른손 법칙방향으로 바깥으로 향한다.
	{
		Triangle3D t;
		std::vector<Triangle3D> tset;
		//윗면
		t.pos1 = Ver[4];
		t.pos2 = Ver[5];
		t.pos3 = Ver[7];
		tset.push_back(t);

		t.pos1 = Ver[6];
		t.pos2 = Ver[7];
		t.pos3 = Ver[5];
		tset.push_back(t);

		//아랫면
		t.pos1 = Ver[0];
		t.pos2 = Ver[3];
		t.pos3 = Ver[1];
		tset.push_back(t);

		t.pos1 = Ver[2];
		t.pos2 = Ver[1];
		t.pos3 = Ver[3];
		tset.push_back(t);
		//앞면
		t.pos1 = Ver[0];
		t.pos2 = Ver[1];
		t.pos3 = Ver[4];
		tset.push_back(t);

		t.pos1 = Ver[5];
		t.pos2 = Ver[4];
		t.pos3 = Ver[1];
		tset.push_back(t);
		//뒷면
		t.pos1 = Ver[2];
		t.pos2 = Ver[3];
		t.pos3 = Ver[6];
		tset.push_back(t);

		t.pos1 = Ver[7];
		t.pos2 = Ver[6];
		t.pos3 = Ver[3];
		tset.push_back(t);
		//오른쪽
		t.pos1 = Ver[1];
		t.pos2 = Ver[2];
		t.pos3 = Ver[5];
		tset.push_back(t);

		t.pos1 = Ver[6];
		t.pos2 = Ver[5];
		t.pos3 = Ver[2];
		tset.push_back(t);
		//왼쪽
		t.pos1 = Ver[0];
		t.pos2 = Ver[4];
		t.pos3 = Ver[3];
		tset.push_back(t);

		t.pos1 = Ver[7];
		t.pos2 = Ver[3];
		t.pos3 = Ver[4];
		tset.push_back(t);

		return tset;

	}

};

class VisionRecognition3DResult
{
public:
//    friend class boost::serialization::access;
    
	std::string name;
	IplImage* cvImage;
	CvMat* mat3d;

	VisionRecognition3DResult() 
	{
		cvImage = NULL;
		mat3d = NULL;
	}

	~VisionRecognition3DResult() 
	{
	}

	//void release()
	//{
	//	if(cvImage) cvReleaseImage(&cvImage);
	//	if(mat3d) cvReleaseMat(&mat3d);
	//}

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & name, cvImage, mat3d;
    }

	VisionRecognition3DResult operator=(const VisionRecognition3DResult &visionRecognition3DResult)
	{
		this->name = visionRecognition3DResult.name;
		this->mat3d = visionRecognition3DResult.mat3d;
		return *this;
	}

};

#endif	//	_API_TYPES_H_