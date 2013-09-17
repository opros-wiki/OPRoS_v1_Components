#ifndef _VisionRecognitionService_PROVIDED_PORT_H
#define _VisionRecognitionService_PROVIDED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

#include "Property.h"
#include "ApiTypes.h"

/*
 * IVisionRecognitionService
 *
 * The comonent inherits this class and implements methods. 
*/
class IVisionRecognitionService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<VisionRecognitionResult> Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)=0;
};

/*
 * 
 * VisionRecognitionService : public ProvidedServicePort
 *
 */
class VisionRecognitionServiceProvided : public ProvidedServicePort, public IVisionRecognitionService
{
protected:
	IVisionRecognitionService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<VisionRecognitionResult> > RecognizeFuncType;
	RecognizeFuncType *RecognizeFunc;


public: // default method
   virtual bool SetParameter(Property parameter)
   {
		assert(SetParameterFunc != NULL);
		
            return (*SetParameterFunc)(parameter);
		
   }
   virtual Property GetParameter()
   {
		assert(GetParameterFunc != NULL);
		
            return (*GetParameterFunc)();
		
   }
   virtual int GetError()
   {
		assert(GetErrorFunc != NULL);
		
            return (*GetErrorFunc)();
		
   }
   virtual vector<VisionRecognitionResult> Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
   {
		assert(RecognizeFunc != NULL);
		
            return (*RecognizeFunc)(image,width,height,pixelBytes);
		
   }


public:
    //
    // Constructor
    //
    VisionRecognitionServiceProvided(IVisionRecognitionService *fn)
    {
        pcom = fn;

        SetParameterFunc = NULL;
        GetParameterFunc = NULL;
        GetErrorFunc = NULL;
        RecognizeFunc = NULL;
        

        setup();
    }

    // generated setup function
    virtual void setup()
    {
        Method *ptr_method;
    
        ptr_method = makeProvidedMethod(&IVisionRecognitionService::SetParameter,pcom,"SetParameter");

        assert(ptr_method != NULL);
        addMethod("SetParameter",ptr_method);
        SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
        ptr_method = NULL;

    
        ptr_method = makeProvidedMethod(&IVisionRecognitionService::GetParameter,pcom,"GetParameter");

        assert(ptr_method != NULL);
        addMethod("GetParameter",ptr_method);
        GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
        ptr_method = NULL;

    
        ptr_method = makeProvidedMethod(&IVisionRecognitionService::GetError,pcom,"GetError");

        assert(ptr_method != NULL);
        addMethod("GetError",ptr_method);
        GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
        ptr_method = NULL;

    
        ptr_method = makeProvidedMethod(&IVisionRecognitionService::Recognize,pcom,"Recognize");

        assert(ptr_method != NULL);
        addMethod("Recognize",ptr_method);
        RecognizeFunc = reinterpret_cast<RecognizeFuncType *>(ptr_method);
        ptr_method = NULL;

    
    }
};
#endif
