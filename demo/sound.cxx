#include <stdio.h>
#include <stdlib.h>
#include <pfcave.h>
#include "dpfSound.h"

int main(int argc,char **argv)
{
 dpfSoundServer *vss;
 dpfSound *sample;
 pfInit();
 pfCAVEConfig(&argc,argv,NULL);
 pfConfig();
 vss = new dpfSoundServer;
 sample = new dpfSound(vss,"sound.aiff");
 sample->play();
 sleep(4);
 vss->kill();
 pfCAVEHalt();
 pfExit();
 return 0;
}
