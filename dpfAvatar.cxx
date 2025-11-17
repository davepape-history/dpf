#include <stdio.h>
#include <math.h>
#include <string.h>
#include <bstring.h>
#include <malloc.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pr/pfGeoState.h>
#include <Performer/pfdu.h>
#include <Performer/pfutil.h>
#include "dpfAvatar.h"


pfType *dpfAvatar::classType_ = NULL; 

void dpfAvatar::init(void)
{
 if (classType_ == NULL)
	{
        pfDCS::init();
        classType_ =  new pfType(pfDCS::getClassType(), "dpfAvatar");
	}
}

dpfAvatar::dpfAvatar(CAVE_USER_ST *user,char *headFile,char *handFile,char *bodyFile)
{
 int i;
 setType(classType_);  // set the Performer type of this instance
 user_ = user;
 dcsList_ = new pfList(sizeof(pfDCS*),1);
 bodyDCS_ = NULL;
 headObject_ = pfdLoadFile(headFile);
 handObject_ = pfdLoadFile(handFile);
 bodyObject_ = pfdLoadFile(bodyFile);
 if (user)
	{
	for (i=0; i < user->num_sensors; i++)
		{
		pfDCS *dcs = new pfDCS;
		if (i)
			{
			if (handObject_)
				dcs->addChild(handObject_);
			}
		else
			{
			if (headObject_)
				dcs->addChild(headObject_);
			}
		addChild(dcs);
		dcsList_->add((void*)dcs);
		}
	bodyDCS_ = new pfDCS;
	if (bodyObject_)
		bodyDCS_->addChild(bodyObject_);
	addChild(bodyDCS_);
	}
}

void dpfAvatar::setUser(CAVE_USER_ST *user)
{
 int i;
 user_ = user;
/* NOTE: need to pfDelete all the dcs's first */
 for (i=0; i < dcsList_->getNum(); i++)
	removeChild((pfDCS *) dcsList_->get(i));
 dcsList_->reset();
 if (user)
	for (i=0; i < user->num_sensors; i++)
		{
		pfDCS *dcs = new pfDCS;
		if (i)
			{
			if (handObject_)
				dcs->addChild(handObject_);
			}
		else
			{
			if (headObject_)
				dcs->addChild(headObject_);
			}
		addChild(dcs);
		dcsList_->add((void*)dcs);
		bodyDCS_ = new pfDCS;
		if (bodyObject_)
			bodyDCS_->addChild(bodyObject_);
		addChild(bodyDCS_);
		}
}

void dpfAvatar::update(void)
{
 int i;
 if (!user_)
	return;
 for (i=0; i < user_->num_sensors; i++)
	{
	pfDCS *dcs = (pfDCS *)dcsList_->get(i);
	if (dcs)
		{
		float pos[3],ori[3];
		CAVEGetSensorPosition(&(user_->sensor[i]),CAVE_NAV_FRAME,pos);
		dcs->setTrans(pos[0],pos[1],pos[2]);
		CAVEGetSensorOrientation(&(user_->sensor[i]),CAVE_NAV_FRAME,ori);
		dcs->setRot(ori[2],ori[0],ori[1]);
		}
	}
 if (bodyDCS_)
	{
	float pos[3],ori[3];
	CAVEGetSensorPosition(&(user_->sensor[0]),CAVE_NAV_FRAME,pos);
	pos[2] -= 3.0f;
	bodyDCS_->setTrans(pos[0],pos[1],pos[2]);
	CAVEGetSensorOrientation(&(user_->sensor[0]),CAVE_NAV_FRAME,ori);
	bodyDCS_->setRot(ori[2],0.0,0.0);
	}
}


#if 0
static void createObject(pfGroup *parent)
{
 pfGeode *geode = new pfGeode;
 pfGeoSet *sphere = pfdNewSphere(12,pfGetSharedArena());
 pfGeoState *gstate = new pfGeoState;
 float *colors = (float *)pfMalloc(4*sizeof(float),pfGetSharedArena());
 colors[0] = 1;
 colors[1] = 1;
 colors[2] = 1;
 colors[3] = 1;
 sphere->setAttr(PFGS_COLOR4,PFGS_OVERALL,colors,NULL);
 sphere->setDrawMode(PFGS_WIREFRAME,PF_ON);
 gstate->setMode(PFSTATE_ENLIGHTING,1);
 sphere->setGState(gstate);
 geode->addGSet(sphere);
 parent->addChild(geode);
}
#endif
