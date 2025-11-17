#ifndef _dpfSound_h_
#define _dpfSound_h_

#include "dpfVolume.h"
#include <Performer/pr/pfList.h>
#include <Performer/pf/pfGroup.h>



class dpfSoundServer
	{
	public:
	 dpfSoundServer(int doconnect=1);
	 ~dpfSoundServer(void);
	 void kill(void);
	 void stopAllSounds(void);
	 void setDefaultDirectory(char *dir);
	 char *defaultDirectory(void);
	 void connect(void);
	 int isConnected(void);
	 void addSound(class dpfSound *sound);
	private:
	 char *defaultDirectory_;
	 int connected_;
	 pfList *sounds_;
	};



class dpfSound : public pfGroup
	{
	public:
	 dpfSound(dpfSoundServer *server,char *file=NULL,float duration=0.0f,float amplitude=1.0f);
	 virtual void	play(void);
	 virtual void	stop(void);
	 virtual void	kill(void);
	 virtual void	restart(void);
	 virtual void	addFile(char *filename,float duration=0.0f);
	 virtual void	setAmplitude(float v);
	 virtual void	setDirectory(char *);
	 virtual void	setLoop(int loop=1);
	 virtual float	amplitude(void);
	 virtual char *	directory(void);
	 virtual int	loop(void);
	 static  void	stopSoundsInTree(pfNode *root);
	 static  void	playSoundsInTree(pfNode *root);
	protected:
	 pfList *files_;
	 float amplitude_;
	 char *directory_;
	 int loop_;
	 dpfSoundServer *server_;
	 float actor_,note_;
	 struct _soundFile { char *filename; float duration; };
	/* Stuff required to make this a Performer class */
	public:
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	};

#endif
