#ifndef	_PROPERTY_H_
#define	_PROPERTY_H_

#include <map>
#include <string>
#include <vector>
#include <boost/serialization/split_member.hpp>
#include <boost/operators.hpp>

using namespace std;

class Property
{
public:
	Property(void) { };
	virtual ~Property(void) { };

private:
	map<string, string> data;

public:
	bool ret;

public:
	friend class boost::serialization::access;

	template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & ret & data;
    }

	Property operator=(const Property &data)
	{
		this->ret = data.ret;
		this->data = data.data;
		
		return *this;
	}

	void SetProperty(map<string, string> data)
	{
		this->data = data;
	}

	map<string, string> GetProperty(void)
	{
		return data;
	}

	void SetValue(string name, string value)
	{
		data[name] = value;
	}

	std::string GetValue(string name)
	{
		return data[name];
	}

	bool FindName(string name)
	{
		if(data.find(name) != data.end()) {
			return true;
		}

		return false;
	}
};

#endif	//	_PROPERTY_H_