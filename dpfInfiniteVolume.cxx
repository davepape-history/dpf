#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "dpfInfiniteVolume.h"

dpfInfiniteVolume::dpfInfiniteVolume(void)
{
}


float dpfInfiniteVolume::distance(const pfVec3 &)
{
 return 0;
}

float dpfInfiniteVolume::sqrDistance(const pfVec3 &)
{
 return 0;
}


int dpfInfiniteVolume::contains(const pfVec3 &)
{
 return TRUE;
}

int dpfInfiniteVolume::isect(const pfSeg *s,float *d0,float *d1)
{
 if (d0)
	*d0 = 0;
 if (d1)
	*d1 = s->length;
 return PFIS_MAYBE | PFIS_TRUE | PFIS_ALL_IN | PFIS_START_IN | PFIS_END_IN;
}

void dpfInfiniteVolume::makeEmpty(void)
{
}

void dpfInfiniteVolume::extendBy(const pfVec3 &)
{
}

void dpfInfiniteVolume::extendBy(const pfBox *)
{
}

void dpfInfiniteVolume::extendBy(const pfSphere *)
{
}

void dpfInfiniteVolume::extendBy(const pfCylinder *)
{
}

void dpfInfiniteVolume::around(const pfVec3 *,int)
{
}

void dpfInfiniteVolume::around(const pfBox **,int)
{
}

void dpfInfiniteVolume::around(const pfSphere **,int)
{
}

void dpfInfiniteVolume::around(const pfCylinder **,int)
{
}
