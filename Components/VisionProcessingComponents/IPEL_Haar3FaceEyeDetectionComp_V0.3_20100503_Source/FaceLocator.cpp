// This is the main DLL file.
#include "FaceLocator.h"


char* FaceCascade = "haarcascade_frontalface_alt.xml";
char* RightEyeCascade = "eyeR.xml";
char* LeftEyeCascade = "eyeL.xml";


FaceLocator::FaceLocator(void)
{
	FaceDetector = new ObjectLocator();
	LeftEyeDetector = new ObjectLocator();
	RightEyeDetector = new ObjectLocator();

	FaceDetector->SetScale(2.0);
	LeftEyeDetector->SetScale(2.0);
	RightEyeDetector->SetScale(2.0);
}

FaceLocator::~FaceLocator(void)
{	
	delete FaceDetector;	
	delete LeftEyeDetector;	
	delete RightEyeDetector;	
}

void FaceLocator::InitCascades(void)
{
	if( FaceDetector->InitObjectDetect(FaceCascade)==0 ||
 		LeftEyeDetector->InitObjectDetect(LeftEyeCascade)==0 ||
		RightEyeDetector->InitObjectDetect(RightEyeCascade)==0) 
	{
		printf("Can not loaded cascades!\n");
		printf("Cascade file for face detection not found. (%s,%s,%s)\n",FaceCascade,LeftEyeCascade,RightEyeCascade);
	}
}

int FaceLocator::DetectFaces(IplImage* inputImage)
{
	if(InitFlag==0) 
	{
		InitFlag++;
		FaceDetector->InitImageStorage(inputImage->width,inputImage->height);
		LeftEyeDetector->InitImageStorage(inputImage->width,inputImage->height);
		RightEyeDetector->InitImageStorage(inputImage->width,inputImage->height);
		InitCascades();	
		lastHeight = inputImage->height;
		lastWidth = inputImage->width;
	}	
	else if((lastHeight!=inputImage->height) || (lastWidth!=inputImage->width))
	{	
		FaceDetector->InitImageStorage(inputImage->width,inputImage->height);
		LeftEyeDetector->InitImageStorage(inputImage->width,inputImage->height);
		RightEyeDetector->InitImageStorage(inputImage->width,inputImage->height);
		InitCascades();
		lastHeight = inputImage->height;
		lastWidth = inputImage->width;
	}
	
	FaceDetector->ManagedImagetoUnManagedImage((inputImage));
	FaceDetector->ImagePreProcessForFaceDetection();
	int FNum = FaceDetector->DetectObjects();

	return FNum;
}


int FaceLocator::GetFaceCordinates(int index, int &lx, int &ly, int &rx, int &ry)
{
	return FaceDetector->GetObjectCoordinates(index, lx, ly, rx, ry);
}

int FaceLocator::GetEyeCordinates(IplImage* inputImage,int index, int &lx, int &ly, int &rx, int &ry)
{
	int leftEyeIndex=-1, rightEyeIndex=-1;
	double minArea=MaxValue, minArea2=MaxValue;
	int minRX, minRY, minRWidth, minRHeight;
	int minLX, minLY, minLWidth, minLHeight;
	
	int xVal1=-1, xVal2=-1;
	
	int LeftPossibleEyes[MAXOBJECTCOUNT];
	int RightPossibleEyes[MAXOBJECTCOUNT];
	int REyeCounter=0,LEyeCounter=0;

	int faceX, faceY, faceWidth, faceHeight;
	int faceMidy;

	int currX, currY, currWidth, currHeight;
	int currMidy, currMidx;
	
	FaceDetector->GetObjectCoordinates(index, faceX, faceY, faceWidth, faceHeight);
	faceMidy = faceY + (faceHeight/2);
	
	//if(FaceDetector->NoOfObjects==1)
	{	
		// detect eyes
		LeftEyeDetector->ManagedImagetoUnManagedImage((inputImage));
		LeftEyeDetector->ImagePreProcessForFaceDetection();
		int LENum = LeftEyeDetector->DetectObjects();

		RightEyeDetector->ManagedImagetoUnManagedImage((inputImage));
		RightEyeDetector->ImagePreProcessForFaceDetection();
		int RENum = RightEyeDetector->DetectObjects();
		
		//prune according to size limits
		for(int i=0; i<LENum;i++)
		{
			LeftEyeDetector->GetObjectCoordinates( i, currX, currY, currWidth, currHeight);
			currMidy = currY + (currHeight/2);
			currMidx = currX + (currWidth/2);

			int ERadius = (currWidth + currHeight) / 2;

			//should be in upper and lower limit
			if((ERadius<=MAXEYERAD && ERadius>=MINEYERAD)
				//center of object should be in upper half of face region
				&& (currMidy <= faceMidy)
				&& (currMidy >= (faceMidy/2))
				&& (currMidx < faceX+(int)((float)faceWidth*(float)0.5))
				&& (currMidx > faceX))
			{
				LeftPossibleEyes[LEyeCounter++] = i;
			}			
		}

		//prune according to size limits
		for(int i=0; i<RENum;i++)
		{
			RightEyeDetector->GetObjectCoordinates( i, currX, currY, currWidth, currHeight);			
			currMidy = currY + (currHeight/2);
			currMidx = currX + (currWidth/2);

			int ERadius = (currWidth + currHeight) / 2;

			//should be in upper and lower limit
			if((ERadius<=MAXEYERAD && ERadius>=MINEYERAD)
				//center of object should be in upper half of face region
				&& (currMidy <= faceMidy)
				&& (currMidy >= (faceMidy/2))
				&& (currMidx < faceX+faceWidth)
				&& (currMidx > faceX+(int)((float)faceWidth*(float)0.5)))
			{
				RightPossibleEyes[REyeCounter++] = i;
			}			
		}

		//doing this we wil get the smallest two objects 
		if(LEyeCounter>0) {
			for(int j=0; j<LEyeCounter;j++)
			{
				LeftEyeDetector->GetObjectCoordinates( LeftPossibleEyes[j], currX, currY, currWidth, currHeight);
				
				//get two objects with smallest areas
				int currArea = currWidth * currHeight;
				if(minArea > currArea)
				{
					//new best minimum
					minArea = currArea;
					leftEyeIndex = LeftPossibleEyes[j];				
				}
			}
			//now compute centers of eyes
			LeftEyeDetector->GetObjectCoordinates( leftEyeIndex, minLX, minLY, minLWidth, minLHeight);

			//assign value to by address variables
			lx = minLX + (minLWidth/2);
			ly = minLY + (minLHeight/2);
		}

		if(REyeCounter>0) {
			for(int j=0; j<REyeCounter;j++)
			{
				RightEyeDetector->GetObjectCoordinates( RightPossibleEyes[j], currX, currY, currWidth, currHeight);
				
				//get two objects with smallest areas
				int currArea = currWidth * currHeight;
				if(minArea2 > currArea)
				{
					//new best minimum
					minArea2 = currArea;
					rightEyeIndex = RightPossibleEyes[j];				
				}
			}

			//now compute centers of eyes
			RightEyeDetector->GetObjectCoordinates( rightEyeIndex, minRX, minRY, minRWidth, minRHeight);

			//assign value to by address variables
			rx = minRX + (minRWidth/2);
			ry = minRY + (minRHeight/2);
		}

		//i could detect 1 eye
		if((LEyeCounter>0 && REyeCounter<=0) || (LEyeCounter<=0 && REyeCounter>0)) return 1;

		//i could not detect 2 eyes
		if(LEyeCounter<=0 && REyeCounter<=0) return -1;

		// i detected 2 eyes
		return 2;
	}

	return -1;
}
