#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "dpfBox.h"

dpfBox::dpfBox(void)
{
 pfBox::makeEmpty();
}

dpfBox::dpfBox(pfBox & box)
{
 pfBox::min = box.min;
 pfBox::max = box.max;
}


float dpfBox::sqrDistance(const pfVec3 & v)
{
 float dx,dy,dz;
 if (v[0] >= min[0])
	if (v[0] <= max[0])
		dx = 0;
	else
		dx = v[0] - max[0];
 else
	dx = min[0] - v[0];
 if (v[1] >= min[1])
	if (v[1] <= max[1])
		dy = 0;
	else
		dy = v[1] - max[1];
 else
	dy = min[1] - v[1];
 if (v[2] >= min[2])
	if (v[2] <= max[2])
		dz = 0;
	else
		dz = v[2] - max[2];
 else
	dz = min[2] - v[2];
 return dx*dx + dy*dy + dz*dz;
}


int dpfBox::contains(const pfVec3 &v)
{
 return pfBox::contains(v);
}

int dpfBox::isect(const pfSeg *s,float *d0,float *d1)
{
 return pfBox::isect(s,d0,d1);
}

void dpfBox::makeEmpty(void)
{
 pfBox::makeEmpty();
}

void dpfBox::extendBy(const pfVec3 & v)
{
 pfBox::extendBy(v);
}

void dpfBox::extendBy(const pfBox * box)
{
 pfBox::extendBy(box);
}

void dpfBox::extendBy(const pfSphere * sph)
{
 pfBox tmpbox;
 tmpbox.around(&sph,1);
 pfBox::extendBy(&tmpbox);
}

void dpfBox::extendBy(const pfCylinder * cyl)
{
 pfBox tmpbox;
 tmpbox.around(&cyl,1);
 pfBox::extendBy(&tmpbox);
}

void dpfBox::around(const pfVec3 * vert,int nvert)
{
 pfBox::around(vert,nvert);
}

void dpfBox::around(const pfBox ** boxes,int nboxes)
{
 pfBox::around(boxes,nboxes);
}

void dpfBox::around(const pfSphere ** sph,int nsph)
{
 pfBox::around(sph,nsph);
}

void dpfBox::around(const pfCylinder ** cyl,int ncyl)
{
 pfBox::around(cyl,ncyl);
}
