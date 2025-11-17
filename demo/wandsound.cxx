#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Performer/pf/pfChannel.h>
#include <Performer/pf/pfLightSource.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pf/pfTraverser.h>
#include <Performer/pfdu.h>
#include <pfcave.h>
#include "dpfLocalSound.h"
#include "dpfSphere.h"

static void createScene(pfChannel *chan,dpfSoundServer *);
static int wandUpdate(pfTraverser *trav,void *data);
static int soundUpdate(pfTraverser *trav,void *data);

int main(int argc,char **argv)
{
 dpfSoundServer *vss;
 pfInit();
 pfCAVEConfig(&argc,argv,NULL);
 pfConfig();
 pfCAVEInitChannels();
 if (CAVEConfig->Simulator)
	pfCAVEMasterChan()->getFStats()->setClass(
			PFSTATS_ALL^PFSTATSHW_ENGFXPIPE_FILL, PFSTATS_ON);
 else
	pfCAVEMasterChan()->getFStats()->setClass(PFSTATS_ALL, PFSTATS_OFF);
 vss = new dpfSoundServer;
 createScene(pfCAVEMasterChan(),vss);
 while (!CAVEgetbutton(CAVE_ESCKEY))
	{
	pfSync();
	pfCAVEPreFrame();
	pfFrame();
	pfCAVEPostFrame();
	}
 vss->kill();
 pfCAVEHalt();
 pfExit();
 return 0;
}

static void createScene(pfChannel *chan,dpfSoundServer *vss)
{
 pfScene *scene;
 pfGeoState *gstate;
 pfDCS *dcs;
 dpfLocalSound *sound;
 pfSphere unitSphere;
 scene = new pfScene;
 gstate = new pfGeoState;
 gstate->setMode(PFSTATE_ENLIGHTING, PF_ON);
 gstate->setMode(PFSTATE_CULLFACE, PFCF_OFF);
 scene->setGState(gstate);
 scene->addChild(new pfLightSource);
 dcs = new pfDCS;
 scene->addChild(dcs);
 dcs->setTravFuncs(PFTRAV_APP,wandUpdate,NULL);
/******* Create the localized sound node *******/
 sound = new dpfLocalSound(vss);
 sound->addFile("sound.aiff",1.0);
 unitSphere.center.set(0,0,0);
 unitSphere.radius = 1;
 sound->setVolume(new dpfSphere(unitSphere));
 sound->setMaxDistance(5);
 sound->setLoop(1);
 sound->setTravFuncs(PFTRAV_APP,soundUpdate,NULL);
 dcs->addChild(sound);
/***********************************************/
 chan->setScene(scene);
}


static int wandUpdate(pfTraverser *trav,void *)
{
 pfDCS *wandDcs = (pfDCS *) trav->getNode();
 pfCAVEDCSWandTransform(wandDcs);
 return PFTRAV_CONT;
}


static int soundUpdate(pfTraverser *trav,void *)
{
 dpfLocalSound *sound = (dpfLocalSound *) trav->getNode();
 int cb1 = CAVEButtonChange(1);
 if (cb1 == 1)
	sound->play();
 else if (cb1 == -1)
	sound->stop();
 return PFTRAV_CONT;
}
