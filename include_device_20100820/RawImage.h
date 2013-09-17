/*
 *  OPRoS Component Engine (OCE)
 *  Copyright (c) 2008 ETRI. http://www.etri.re.kr.
 *  Distributed under the OPRoS License, Version 1.0.
 *
 *  @Created : 2009. 3. 13
 *  @Author  : sby (sby@etri.re.kr)
 *
 *  @File    : RawImage.h
 *
 *
 */

#ifndef _RAWIMAGE_H
#define _RAWIMAGE_H

#include <boost/serialization/split_member.hpp>
#include <boost/shared_ptr.hpp>
#include <memory.h>

class RawImageData {
protected:
	unsigned char *m_data;
	int m_width;
	int m_height;
	int m_pixelByte;
	unsigned long m_size;

public:
	RawImageData(int width, int height, int pixelByte)
	{
		m_width = width;
		m_height = height;
		m_pixelByte = pixelByte;

		m_size = m_width * m_height * m_pixelByte;

		m_data = new unsigned char[m_size];
	}

	RawImageData(RawImageData &ptr)
	{
		m_width = ptr.getWidth();
		m_height = ptr.getHeight();
		m_pixelByte = ptr.getPixelByte();

		m_size = ptr.getSize();

		m_data = new unsigned char[m_size];
		
		memcpy(m_data, ptr.getData(), m_size);
	}

	RawImageData()
	{
		m_data = 0;
		m_size = 0;
		m_width = 0;
		m_height = 0;
		m_pixelByte = 0;
	}

	virtual ~RawImageData()
	{
		if (m_data != NULL)
			delete m_data;
	}

	RawImageData(unsigned char *data, int width, int height, int pixelByte)
	{
		m_width = width;
		m_height = height;
		m_pixelByte = pixelByte;
		m_size = m_width * m_height * m_pixelByte;
		m_data = new unsigned char[m_size];

		memcpy(m_data, data, m_size);
	}

	void reset(RawImageData &p)
	{
		unsigned char *pdata = p.getData();
		reset(pdata, p.getWidth(), p.getHeight(), p.getPixelByte());
	}

	void reset(unsigned char *data, int width, int height, int pixelByte)
	{
		unsigned long  n_size = width * height * pixelByte;
		
		if (m_data == NULL) 
		{
			m_size = n_size;
			m_data = new unsigned char [m_size];
		}
		else
		if (m_size < n_size)
		{
			if (m_data != NULL) delete m_data;
			m_size = n_size;
			m_data = new unsigned char [m_size];
		}

		m_width = width;
		m_height = height;
		m_pixelByte = pixelByte;
		
		memcpy(m_data, data, n_size);
	}

	void resize(int width, int height, int pixelByte)
	{
		if (m_data != NULL) delete m_data;
		m_width = width;
		m_height = height;
		m_pixelByte = pixelByte;
		m_size = m_width * m_height * m_pixelByte;
		m_data = new unsigned char[m_size];
	}

	unsigned char *getData()
	{
		return m_data;
	}

	unsigned long getSize()
	{
		return m_size;
	}

	int getWidth()
	{
		return m_width;
	}

	int getHeight()
	{
		return m_height;
	}

	int getPixelByte()
	{
		return m_pixelByte;
	}
};

class RawImage {
	friend class boost::serialization::access;

	boost::shared_ptr<RawImageData> m_image;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {

		ar & BOOST_SERIALIZATION_NVP(m_image);
	}

public:
	RawImage() : m_image(new RawImageData) {
	}
	RawImage(RawImageData &ptr) : m_image( new RawImageData(ptr)) {
	}

	RawImage(const RawImage &rht) {
		m_image = rht.m_image;
	}

	virtual ~RawImage()
	{
	}

	RawImageData *getImage() {
		return m_image.get();
	}

	void setImage(RawImageData *ptr) {
		m_image.reset(ptr);
	}


	RawImage &operator=(const RawImage &rhs) {
		m_image = rhs.m_image;
		return *this;
	}
};


namespace boost {
namespace serialization {

template<class Archive>
inline void save_this(Archive &ar, RawImageData &g,const unsigned int file_version) {

	std::string cdibname("raw");


	ar & boost::serialization::make_nvp("raw",cdibname);

	int width = g.getWidth();
	int height = g.getHeight();
	int pixelByte = g.getPixelByte();

	unsigned long size = g.getSize();

	ar & BOOST_SERIALIZATION_NVP(width);
	ar & BOOST_SERIALIZATION_NVP(height);
	ar & BOOST_SERIALIZATION_NVP(pixelByte);
	ar & BOOST_SERIALIZATION_NVP(size);

	ar.save_binary( g.getData(), size);
}

template<class Archive>
inline void save(Archive &ar, const RawImageData &t,
		const unsigned int file_version) {

	 save_this(ar,(RawImageData &)t,file_version);
}

template<class Archive>
inline void load(Archive & ar, RawImageData &g, const unsigned int file_version) {

	std::string cdibname;

	ar & boost::serialization::make_nvp("raw",cdibname);

	int width;
	int height;
	int pixelByte;

	unsigned long size = 0;

	ar & BOOST_SERIALIZATION_NVP(width);
	ar & BOOST_SERIALIZATION_NVP(height);
	ar & BOOST_SERIALIZATION_NVP(pixelByte);
	ar & BOOST_SERIALIZATION_NVP(size);

	g.resize(width, height, pixelByte);

	ar.load_binary(g.getData(), size);
 ;
}

template<class Archive>
void serialize(Archive & ar, RawImageData & g, const unsigned int version) {
	boost::serialization::split_free(ar, g, version);
}

} // namespace serialization
}
#endif /* _RAWIMAGE_H */
