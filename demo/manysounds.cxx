#include <stdio.h>
#include <stdlib.h>
#include <pfcave.h>
#include "dpfSound.h"

int main(int argc,char **argv)
{
 int num,i;
 dpfSoundServer *vss;
 dpfSound *sample[1024];
 pfInit();
 pfCAVEConfig(&argc,argv,NULL);
 pfConfig();
 vss = new dpfSoundServer;
 num = atoi(argv[1]);
 for (i=0; i < num; i++)
	{
	char file[256];
	sprintf(file,"sound%d.aiff",i%8);
	sample[i] = new dpfSound(vss,file,0.0,1.0/num);
	sample[i]->setLoop();
	}
 for (i=0; i < num; i++)
	sample[i]->play();
 sleep(12);
 vss->kill();
 pfCAVEHalt();
 pfExit();
 return 0;
}
