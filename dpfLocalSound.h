#ifndef _dpfLocalSound_h_
#define _dpfLocalSound_h_

#include "dpfVolume.h"
#include "dpfSound.h"



class dpfLocalSound : public dpfSound
	{
	public:
	 dpfLocalSound(dpfSoundServer *server,char *file=NULL,float duration=0.0f,
				float amplitude=1.0f);
	 virtual void	play(void);
	 virtual void	stop(void);
	 virtual int	isPlaying(void);
	 virtual void	setLoop(int);
	 virtual void	setVolume(dpfVolume *v);
	 virtual void	setMaxDistance(float v);
	 virtual dpfVolume * volume(void);
	 virtual float	maxDistance(void);
	 virtual void	useNavPosition(int flag=1);
	 virtual int	app(pfTraverser*);
	 virtual int	needsApp(void);
	protected:
	 virtual float computeAmplitude(pfVec3 userPos);
	 float maxDistance_, maxDistanceSq_;
	 dpfVolume *volume_;
	 float startTime_,endTime_;
	 float curAmpl_;
	 int useNavFlag_;
	/* Stuff required to make this a Performer class */
	public:
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	};

#endif
