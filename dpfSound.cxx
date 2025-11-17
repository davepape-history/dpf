#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <vssClient.h>
#include "dpfSound.h"



dpfSoundServer::dpfSoundServer(int doconnect)
{
 defaultDirectory_ = NULL;
 connected_ = 0;
 sounds_ = new pfList;
 if (doconnect)
	connect();
}

dpfSoundServer::~dpfSoundServer(void)
{
 kill();
}

void dpfSoundServer::kill(void)
{
 if (connected_)
	{
	int i;
	for (i=0; i < sounds_->getNum(); i++)
		((dpfSound *) sounds_->get(i))->kill();
	EndSoundServer();
	connected_ = 0;
	}
}

void dpfSoundServer::stopAllSounds(void)
{
 if (connected_)
	{
	int i;
	for (i=0; i < sounds_->getNum(); i++)
		((dpfSound *) sounds_->get(i))->stop();
	}
}

void dpfSoundServer::setDefaultDirectory(char *dir)
{
 if (defaultDirectory_)
	pfFree(defaultDirectory_);
 if (dir)
	defaultDirectory_ = pfStrdup(dir,pfGetSharedArena());
 else
	defaultDirectory_ = NULL;
}

char *dpfSoundServer::defaultDirectory(void)
{
 return defaultDirectory_;
}

void dpfSoundServer::connect(void)
{
 if (connected_)
	kill();
 connected_ =  BeginSoundServer();
 if (!connected_)
	fprintf(stderr,"WARNING: dpfSoundServer failed to connect\n");
 else
	{
	int i;
	for (i=0; i < sounds_->getNum(); i++)
		((dpfSound *) sounds_->get(i))->restart();
	}
}

int dpfSoundServer::isConnected(void)
{
 return connected_;
}

void dpfSoundServer::addSound(dpfSound *sound)
{
 sounds_->add(sound);
}



/*---------------------------------------------------------------------------*/



pfType *dpfSound::classType_ = NULL; 

void dpfSound::init(void)
{
 if (classType_ == NULL)
	{
        pfGroup::init();
        classType_ =  new pfType(pfGroup::getClassType(), "dpfSound");
	}
}



dpfSound::dpfSound(dpfSoundServer *server,char *file,float duration,float amplitude)
{
 setType(classType_);  // set the Performer type of this instance
 amplitude_ = amplitude;
 note_ = -1;
 directory_ = NULL;
 loop_ = 0;
 server_ = server;
 files_ = new pfList;
 if (server_->isConnected())
	{
	actor_ = actorMessage(A_Create,"F",(float)SampleActor);
	if (server_->defaultDirectory())
		actorMessage(A_SetDirectory,"FS",actor_,server_->defaultDirectory());
	}
 else
	actor_ = -1;
 server_->addSound(this);
 if (file)
	addFile(file,duration);
}

void dpfSound::kill(void)
{
 if (actor_ > -1)
	{
	actorMessage(A_EndAllNotes,"F",actor_);
	actorMessage(A_Delete,"F",actor_);
	actor_ = -1;
/* If we are looping, leave note_ unchanged; this allows a  kill();restart();
		to restart the note if it was in the middle of playing */
	if (!loop_)
		note_ = -1;
	}
}

void dpfSound::restart(void)
{
 if (server_->isConnected())
	{
	actor_ = actorMessage(A_Create,"F",(float)SampleActor);
	if (directory_)
		actorMessage(A_SetDirectory,"FS",actor_,directory_);
	else if (server_->defaultDirectory())
		actorMessage(A_SetDirectory,"FS",actor_,server_->defaultDirectory());
	if (note_ > -1)
		{
		note_ = -1;
		play();
		}
	}
}


void dpfSound::play(void)
{
 if ((note_ == -1) && (actor_ > -1) && (files_->getNum() > 0))
	{
	struct _soundFile *sf;
	sf = (struct _soundFile *) files_->get(random() % files_->getNum());
	note_ = actorMessage(A_BeginNote, "FFFS", actor_, 1.0, amplitude_, sf->filename);
	if (note_ == -1)
		return;
	if (loop_)
		actorMessage(A_SetLoop, "FFF", actor_, note_, 1.0);
	}
}

void dpfSound::stop(void)
{
 if (note_ > -1)
	{
	if (actor_ > -1)
		actorMessage(A_EndAllNotes,"F",actor_);
	note_ = -1;
	}
}


void dpfSound::addFile(char *filename,float duration)
{
 struct _soundFile *sf;
 sf = (struct _soundFile *) pfMalloc(sizeof(struct _soundFile),pfGetSharedArena());
 sf->filename = pfStrdup(filename,pfGetSharedArena());
 sf->duration = duration;
 files_->add(sf);
}

void dpfSound::setAmplitude(float a)
{
 amplitude_ = a;
}

void dpfSound::setLoop(int loop)
{
 loop_ = loop;
 if ((actor_ > -1) && (note_ > -1))
	{
	actorMessage(A_SetLoop, "FFF", actor_, note_, (float)loop_);
	}
}

void dpfSound::setDirectory(char *dir)
{
 if (directory_)
	pfFree(directory_);
 if (dir)
	{
	directory_ = pfStrdup(dir,pfGetSharedArena());
	if (actor_ > -1)
		actorMessage(A_SetDirectory,"FS",actor_,directory_);
	}
 else
	directory_ = NULL;
}


float dpfSound::amplitude(void)
{
 return amplitude_;
}

char * dpfSound::directory(void)
{
 return directory_;
}

int dpfSound::loop(void)
{
 return loop_;
}


void dpfSound::stopSoundsInTree(pfNode *node)
{
 int i;
 if (node->isOfType(dpfSound::getClassType()))
	{
	((dpfSound *)node)->stop();
	}
 else if (node->isOfType(pfGroup::getClassType()))
	{
	pfGroup *group = (pfGroup *)node;
	for (i=0; i < group->getNumChildren(); i++)
		{
		stopSoundsInTree(group->getChild(i));
		}
	}
}


void dpfSound::playSoundsInTree(pfNode *node)
{
 int i;
 if (node->isOfType(dpfSound::getClassType()))
	{
	((dpfSound *)node)->play();
	}
 else if (node->isOfType(pfGroup::getClassType()))
	{
	pfGroup *group = (pfGroup *)node;
	for (i=0; i < group->getNumChildren(); i++)
		{
		playSoundsInTree(group->getChild(i));
		}
	}
}
