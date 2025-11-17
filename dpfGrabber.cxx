#include <stdio.h>
#include <math.h>
#include <string.h>
#include <bstring.h>
#include <malloc.h>
#include "dpfGrabber.h"



pfType *dpfGrabber::classType_ = NULL; 

void dpfGrabber::init(void)
{
 if (classType_ == NULL)
	{
        pfDCS::init();
        classType_ =  new pfType(pfDCS::getClassType(), "dpfGrabber");
	}
}

dpfGrabber::dpfGrabber(CAVE_SENSOR_ST *sensor)
{
 setType(classType_);  // set the Performer type of this instance
 sensor_ = sensor;
 grabbed_ = 0;
 grabMat_.makeIdent();
}

int dpfGrabber::isGrabbed(void)
{
 return grabbed_;
}

void dpfGrabber::setSensor(CAVE_SENSOR_ST *sensor)
{
 int wasGrabbed = grabbed_;
 if (wasGrabbed)
	release();
 sensor_ = sensor;
 if (wasGrabbed)
	grab();
}

void dpfGrabber::grab(void)
{
 if (!grabbed_)
	{
	pfMatrix invmat;
	GetInverseSensorMatrix(invmat);
	getMat(grabMat_);
	grabMat_ *= invmat;
	grabbed_ = 1;
	update();
	}
}

void dpfGrabber::release(void)
{
 if (grabbed_)
	{
	update();
	grabbed_ = 0;
	}
}

void dpfGrabber::update(void)
{
 if (grabbed_)
	{
	pfMatrix sensMat, newMat;
	GetSensorMatrix(sensMat);
	newMat = grabMat_ * sensMat;
	setMat(newMat);
	}
}

void dpfGrabber::GetSensorMatrix(pfMatrix& m)
{
 float or[3],pos[3];
 CAVEGetSensorPosition(sensor_,CAVE_NAV_FRAME,pos); 
 CAVEGetSensorOrientation(sensor_,CAVE_NAV_FRAME,or);
 m.makeTrans(pos[0],pos[1],pos[2]);
 m.preRot(or[2],0.0,0.0,1.0,m);
 m.preRot(or[0],1.0,0.0,0.0,m);
 m.preRot(or[1],0.0,1.0,0.0,m);
}

void dpfGrabber::GetInverseSensorMatrix(pfMatrix& m)
{
 float or[3],pos[3];
 CAVEGetSensorPosition(sensor_,CAVE_NAV_FRAME,pos); 
 CAVEGetSensorOrientation(sensor_,CAVE_NAV_FRAME,or);
 m.makeRot(-or[1],0.0,1.0,0.0);
 m.preRot(-or[0],1.0,0.0,0.0,m);
 m.preRot(-or[2],0.0,0.0,1.0,m);
 m.preTrans(-pos[0],-pos[1],-pos[2],m);
}
