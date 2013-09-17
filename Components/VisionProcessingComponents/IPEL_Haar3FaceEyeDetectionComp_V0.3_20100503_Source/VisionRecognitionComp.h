
#ifndef _VisionRecognitionComp_COMPONENT_H
#define _VisionRecognitionComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>


#include "VisionRecognitionServiceProvided.h"
	

class VisionRecognitionComp: public Component
	,public IVisionRecognitionService
{
protected:


public:
	VisionRecognitionComp();
	VisionRecognitionComp(const std::string &compId);
	virtual ~VisionRecognitionComp();
	virtual void portSetup();

protected:
	virtual ReturnType onInitialize();
	virtual ReturnType onStart();
	virtual ReturnType onStop();
	virtual ReturnType onReset();
	virtual ReturnType onError();
	virtual ReturnType onRecover();
	virtual ReturnType onDestroy();

public:
	virtual ReturnType onEvent(Event *evt);
	virtual ReturnType onExecute();
	virtual ReturnType onUpdated();
	virtual ReturnType onPeriodChanged();

	virtual bool SetParameter(Property parameter);
	virtual Property GetParameter();
	virtual int GetError();
	virtual vector<VisionRecognitionResult> Recognize(vector<unsigned char> image,int width,int height,int pixelBytes);
};

#endif

