#include <stdio.h>
#include <math.h>
#include <string.h>
#include <bstring.h>
#include <malloc.h>
#include <Performer/pf/pfTraverser.h>
#include <pfcave.h>
#define Boolean int
#include <vssClient.h>
#undef Boolean
#include "dpfLocalSound.h"



pfType *dpfLocalSound::classType_ = NULL; 

void dpfLocalSound::init(void)
{
 if (classType_ == NULL)
	{
        dpfSound::init();
        classType_ =  new pfType(dpfSound::getClassType(), "dpfLocalSound");
	}
}






dpfLocalSound::dpfLocalSound(dpfSoundServer *server,char *file,float duration,float amplitude)
	: dpfSound(server,file,duration,amplitude)
{
 setType(classType_);  // set the Performer type of this instance
 maxDistance_ = 10;
 maxDistanceSq_ = 100;
 volume_ = NULL;
 startTime_ = 0;
 endTime_ = 0;
 curAmpl_ = 0;
 useNavFlag_ = 0;
}


int dpfLocalSound::app(pfTraverser *trav)
{
 if ((note_ > -1) && (actor_ > -1))
	{
	if ((endTime_ > -1) && (pfGetTime() > endTime_))
		stop();
	else
		{
		pfVec3 headPos, headPosLocal;
		pfMatrix xform, invXform;
		float newAmpl;
		trav->getMat(xform);
		invXform.invertAff(xform);
		if (useNavFlag_)
			CAVEGetPosition(CAVE_HEAD_NAV,headPos.vec);
		else
			CAVEGetPosition(CAVE_HEAD,headPos.vec);
		headPosLocal.xformPt(headPos,invXform);
		newAmpl = computeAmplitude(headPosLocal);
		if (fabs(newAmpl - curAmpl_) > 0.005)
			{
			curAmpl_ = newAmpl;
			actorMessage(A_SetAmpl,"FFF",actor_,note_,curAmpl_);
			}
		}
	}
 return dpfSound::app(trav);
}

int dpfLocalSound::needsApp(void)
{
 return TRUE;
}


void dpfLocalSound::play(void)
{
 if ((note_ == -1) && (actor_ > -1) && (files_->getNum() > 0))
	{
	struct _soundFile *sf;
	sf = (struct _soundFile *) files_->get(random() % files_->getNum());
	curAmpl_ = 0;
	note_ = actorMessage(A_BeginNote, "FFFS", actor_, 1.0, curAmpl_, sf->filename);
	if (note_ == -1)
		return;
	if (loop_)
		actorMessage(A_SetLoop, "FFF", actor_, note_, 1.0);
	startTime_ = pfGetTime();
	if ((loop_) || (sf->duration <= 0.0))
		endTime_ = -1;
	else
		endTime_ = startTime_ + sf->duration;
	}
}

void dpfLocalSound::stop(void)
{
 dpfSound::stop();
 curAmpl_ = 0;
}

int dpfLocalSound::isPlaying(void)
{
 return ((note_ > -1) && (actor_ > -1));
}

float dpfLocalSound::computeAmplitude(pfVec3 userPos)
{
 float distSq;
 if (maxDistanceSq_ < 0)
	return amplitude_;
 if (volume_)
	distSq = volume_->sqrDistance(userPos);
 else
	distSq = userPos.dot(userPos);
 if (distSq >= maxDistanceSq_)
	return 0;
 return amplitude_ * (1.0f - fsqrt(distSq) / maxDistance_);
}



void dpfLocalSound::setLoop(int loop)
{
 dpfSound::setLoop(loop);
 if ((actor_ > -1) && (note_ > -1) && (loop_))
	endTime_ = -1;
}

void dpfLocalSound::setVolume(dpfVolume *v)
{
 volume_ = v;
}

void dpfLocalSound::setMaxDistance(float d)
{
 maxDistance_ = d;
 if (d < 0)
	maxDistanceSq_ = -1;
 else
	maxDistanceSq_ = d * d;
}


dpfVolume * dpfLocalSound::volume(void)
{
 return volume_;
}

float dpfLocalSound::maxDistance(void)
{
 return maxDistance_;
}

void dpfLocalSound::useNavPosition(int flag)
{
 useNavFlag_ = flag;
}
