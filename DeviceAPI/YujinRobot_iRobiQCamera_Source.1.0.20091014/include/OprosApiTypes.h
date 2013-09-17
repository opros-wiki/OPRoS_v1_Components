#ifndef	_OPROS_API_TYPES_H_
#define	_OPROS_API_TYPES_H_

#include <string>
#include <map>
#include <vector>
#include <valarray>
#include <math.h>
#include <boost/serialization/split_member.hpp>
#include <boost/operators.hpp>

using namespace std;

namespace OPRoS
{

enum DEVICE_STATUS {
	DEVICE_CREATED		= 0x00,
	DEVICE_READY		= 0x01,
	DEVICE_ACTIVE		= 0x02,
	DEVICE_ERROR		= 0x03,
};

class Property
{
private:
	std::map<std::string, std::string> data;

public:
	friend class boost::serialization::access;

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & data;
    }

	void setValue(std::string index, std::string value)
	{
		data[index] = value;
	}

	std::string getValue(std::string index)
	{
		return data[index];
	}

	void setProperty(std::map<std::string, std::string> data)
	{
		this->data = data;
	}

	bool findIndex(std::string index)
	{
		if(data.find(index) != data.end()) {
			return true;
		}

		return false;
	}
};

class CANData
{
public:
	friend class boost::serialization::access;

	long id;
	valarray<unsigned char> data;
	
	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & id & data;
	}

	CANData operator=(const CANData &canData)
	{
		this->id = canData.id;
		this->data = canData.data;

		return *this;
	}
};

class ObjectPosition
{
public:
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

class MobilityVelocity
{
public:
	MobilityVelocity() {	forward = 0.0;	angular = 0.0; }
    friend class boost::serialization::access;
    
	double forward;
	double angular;
	    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & forward & angular;
    }
    
    MobilityVelocity operator=(const MobilityVelocity &mobilityVelocity)
    {
		this->forward = mobilityVelocity.forward;
		this->angular = mobilityVelocity.angular;
        
        return *this;
    }
};

class ImageData
{
public:
	ImageData(void)
	{
		width = height = pixelByte = 0;
		image.resize(0);
	}

	int width;
	int height;
	int pixelByte;
	std::valarray<unsigned char> image;

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & width & height & pixelByte & image;
    }
    
    ImageData operator=(const ImageData &imageData)
    {
		this->width = imageData.width;
		this->height = imageData.height;
		this->pixelByte = imageData.pixelByte;
		this->image = imageData.image;
        
        return *this;
    }
};

class ObjectLocation : public boost::operators<ObjectLocation>
{
public:
	double x, y, th;

public:
	friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & x & y & th;
    }

public:
	ObjectLocation () { }
	ObjectLocation (double len, double th_) : x (len * cos (th_)), y (len * sin (th_)), th (th_) { }
	ObjectLocation (double x_, double y_, double th_) : x (x_), y (y_), th (th_) { }

public: 
	ObjectLocation & operator += (const ObjectLocation &p) { x += p.x; y += p.y; th += p.th; return *this; }
	ObjectLocation & operator -= (const ObjectLocation &p) { x -= p.x; y -= p.y; th -= p.th; return *this; }
	ObjectLocation & operator *= (const ObjectLocation &p) { x *= p.x; y *= p.y; th *= p.th; return *this; }
	ObjectLocation & operator /= (const ObjectLocation &p) { x /= p.x; y /= p.y; th /= p.th; return *this; }
	ObjectLocation & operator *= (double d)                { x *= d;   y *= d;   th *= d;    return *this; }

	ObjectLocation &Rotate (double rad)
	{
		double c = cos (rad);
		double s = sin (rad);
		double x_ = x * c - y * s;
		double y_ = x * s + y * c;
		x = x_;
		y = y_;
		th += rad;
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
		Rotate (p.th);
		Translate (p.x, p.y);
		return *this;
	}

	double Atan ()   { return atan2 (y, x); }
	double Length () { return sqrt (x*x + y*y); }
	double Distance (ObjectLocation &p) { double dx = p.x - x, dy = p.y - y; return sqrt (dx * dx + dy * dy); }
};

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
	std::vector<std::valarray<double>> axisPosition;		//reference frame기준 joint frame의 원점 좌표(x,y,z)
	std::vector<std::valarray<double>> axisZ;			//joint frame z-axis(0,0,1)의 reference frame 에 대한 성분(directional cosine)
	std::vector<double> maximumVelocity;
	std::vector<double> acceleration;
	std::vector<double> minimumRange;
	std::vector<double> maximumRange;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & size & id & dhParameter & axisPosition & axisZ & maximumVelocity & acceleration & minimumRange & maximumRange;
	}

	ManipulatorParameter operator=(const ManipulatorParameter &manipulatorParameter)
	{
		this->size = manipulatorParameter.size;
		this->id = manipulatorParameter.id;
		this->dhParameter = manipulatorParameter.dhParameter;
		this->axisPosition = manipulatorParameter.axisPosition;
		this->axisZ = manipulatorParameter.axisZ;
		this->maximumVelocity = manipulatorParameter.maximumVelocity;
		this->acceleration = manipulatorParameter.acceleration;
		this->minimumRange = manipulatorParameter.minimumRange;
		this->maximumRange = manipulatorParameter.maximumRange;

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

};

#endif	//	_OPROS_API_TYPES_H_