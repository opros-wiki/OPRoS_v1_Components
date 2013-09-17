#include <vector>

#include "NiCanImpl.h"

using namespace std;


NiCanImpl::NiCanImpl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, int mode, unsigned long timeOut)
{
	_handle = -1;

	_channel = channel;
	_bitRate = bitRate;
	_acceptanceMask = acceptanceMask;
	_acceptanceCode = acceptanceCode;
	_mode = mode;

	_timeOut = timeOut;
}

NiCanImpl::~NiCanImpl(void)
{
	Close();
}

int NiCanImpl::Open(void)
{
	vector<NCTYPE_ATTRID> attributeID;		attributeID.resize(0);
	vector<NCTYPE_UINT32> attributeValue;	attributeValue.resize(0);

	//	Channel Name
	char channelName[32];
	sprintf_s(channelName, sizeof(channelName) - 1, "CAN%d", _channel);

	switch(_bitRate) {
		case 1000000 :		case 500000 :		case 250000 :	
		case 100000 :		case 50000 :		case 10000 :
			attributeID.push_back(NC_ATTR_BAUD_RATE);		attributeValue.push_back(_bitRate);
			break;
		default :		return -1;
	}

	//	Acceptacne Comparator & Mask
	if(_mode == 0) {
		//	Standard Mode
		attributeID.push_back(NC_ATTR_CAN_COMP_STD);		attributeValue.push_back(_acceptanceCode & 0x7FF);
		attributeID.push_back(NC_ATTR_CAN_MASK_STD);		attributeValue.push_back(_acceptanceMask & 0x7FF);
		attributeID.push_back(NC_ATTR_CAN_COMP_XTD);		attributeValue.push_back(0x00);
		attributeID.push_back(NC_ATTR_CAN_MASK_XTD);		attributeValue.push_back(0x00);

		attributeID.push_back(NC_ATTR_SERIES2_FILTER_MODE);	attributeValue.push_back(NC_FILTER_SINGLE_STANDARD);
		attributeID.push_back(NC_ATTR_SERIES2_COMP);		attributeValue.push_back(_acceptanceCode & 0x7FF);
		attributeID.push_back(NC_ATTR_SERIES2_MASK);		attributeValue.push_back(_acceptanceMask & 0x7FF);

	}
	else {
		//	Extended Mode
		attributeID.push_back(NC_ATTR_CAN_COMP_STD);		attributeValue.push_back(0x00);
		attributeID.push_back(NC_ATTR_CAN_MASK_STD);		attributeValue.push_back(NC_CAN_MASK_STD_DONTCARE);
		attributeID.push_back(NC_ATTR_CAN_COMP_XTD);		attributeValue.push_back(_acceptanceCode & 0x1FFFFFFF);
		attributeID.push_back(NC_ATTR_CAN_MASK_XTD);		attributeValue.push_back(_acceptanceMask & 0x1FFFFFFF);

		attributeID.push_back(NC_ATTR_SERIES2_FILTER_MODE);	attributeValue.push_back(NC_FILTER_SINGLE_EXTENDED);
		attributeID.push_back(NC_ATTR_SERIES2_COMP);		attributeValue.push_back(_acceptanceCode & 0x1FFFFFFF);
		attributeID.push_back(NC_ATTR_SERIES2_MASK);		attributeValue.push_back(_acceptanceMask & 0x1FFFFFFF);
	}

	//	RX & TX FIFO
	attributeID.push_back(NC_ATTR_READ_Q_LEN);			attributeValue.push_back(100);
	attributeID.push_back(NC_ATTR_WRITE_Q_LEN);			attributeValue.push_back(1);

	//	Start on Open
	attributeID.push_back(NC_ATTR_START_ON_OPEN);		attributeValue.push_back(NC_TRUE);

	if(ncConfig(channelName, attributeID.size(), &attributeID[0], &attributeValue[0]) < 0) {
		return -1;
	}

	if(ncOpenObject(channelName, &_handle) < 0) {
		_handle = -1;
		return -1;
	}

	return 0;
}

int NiCanImpl::Close(void)
{
	if(_handle == -1) {
		return 0;
	}

	if(ncCloseObject(_handle) != CanSuccess) {
		return -1;
	}	
	
	_handle = -1;

	return 0;
}

int NiCanImpl::Write(long id, unsigned char *data, int size)
{
	NCTYPE_CAN_FRAME frame;
	NCTYPE_STATE ncState;

	if(size < 0) {
		return -1;
	}
	else if(size > 8) {
		size = 8;
	}
		
	if(_mode == 1) {
		frame.ArbitrationId = id | 0x20000000;
	}
	else {
		frame.ArbitrationId = id;
	}
	memcpy(frame.Data, &data[0], size);

	if(ncWaitForState(_handle, NC_ST_WRITE_SUCCESS, _timeOut, &ncState) < 0) {
		return -1;
	}

	if(ncWrite(_handle, sizeof(frame), &frame) < 0) {
		return -1;
	}	

	return size;
}

int NiCanImpl::Read(long &id, unsigned char *data, int size)
{
	NCTYPE_CAN_FRAME frame;
	NCTYPE_STATE ncState;
	
	if(ncWaitForState(_handle, NC_ST_READ_AVAIL, _timeOut, &ncState) < 0) {
		return -1;
	}

	if(ncRead(_handle, sizeof(frame), &frame) < 0) {
		return -1;
	}

	id = frame.ArbitrationId;
	size = min(size, frame.DataLength);
	memcpy(data, frame.Data, size);

	return size;
}

void NiCanImpl::Lock(void)
{
	lock.Lock();
}

void NiCanImpl::Unlock(void)
{
	lock.Unlock();
}
