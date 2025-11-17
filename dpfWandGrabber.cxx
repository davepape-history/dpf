#include <stdio.h>
#include <math.h>
#include <string.h>
#include <bstring.h>
#include <malloc.h>
#include <cave.h>
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

dpfGrabber::dpfGrabber(void)
{
 setType(classType_);  // set the Performer type of this instance
 grabbed_ = 0;
}

int dpfGrabber::isGrabbed(void)
{
 return grabbed_;
}

void dpfGrabber::grab(void)
{
 if (!grabbed_)
	{
	pfMatrix invmat;
	GetInverseWandMatrix(invmat);
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
	pfMatrix wandMat, newMat;
	GetWandMatrix(wandMat);
	newMat = grabMat_ * wandMat;
	setMat(newMat);
	}
}

void dpfGrabber::GetWandMatrix(pfMatrix& m)
{
 float or[3],pos[3];
 CAVEGetPosition(CAVE_WAND_NAV,pos); 
 CAVEGetOrientation(CAVE_WAND_NAV,or);
 m.makeTrans(pos[0],pos[1],pos[2]);
 m.preRot(or[2],0.0,0.0,1.0,m);
 m.preRot(or[0],1.0,0.0,0.0,m);
 m.preRot(-or[1],0.0,1.0,0.0,m);
}

void dpfGrabber::GetInverseWandMatrix(pfMatrix& m)
{
 float or[3],pos[3];
 CAVEGetPosition(CAVE_WAND_NAV,pos); 
 CAVEGetOrientation(CAVE_WAND_NAV,or);
 m.makeRot(or[1],0.0,1.0,0.0);
 m.preRot(-or[0],1.0,0.0,0.0,m);
 m.preRot(-or[2],0.0,0.0,1.0,m);
 m.preTrans(-pos[0],-pos[1],-pos[2],m);
}
