#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "dpfSphere.h"

dpfSphere::dpfSphere(void)
{
 pfSphere::makeEmpty();
}

dpfSphere::dpfSphere(pfSphere & sph)
{
 pfSphere::center = sph.center;
 pfSphere::radius = sph.radius;
}


float dpfSphere::distance(const pfVec3 & v)
{
 float centerDistSq = v.sqrDistance(center);
 if (centerDistSq <= radius * radius)
	return 0.0f;
 return fsqrt(centerDistSq) - radius;
}


float dpfSphere::sqrDistance(const pfVec3 & v)
{
 float dist = distance(v);
 return dist * dist;
}


int dpfSphere::contains(const pfVec3 &v)
{
 return pfSphere::contains(v);
}

int dpfSphere::isect(const pfSeg *s,float *d0,float *d1)
{
 return pfSphere::isect(s,d0,d1);
}

void dpfSphere::makeEmpty(void)
{
 pfSphere::makeEmpty();
}

void dpfSphere::extendBy(const pfVec3 & v)
{
 pfSphere::extendBy(v);
}

void dpfSphere::extendBy(const pfBox * box)
{
 pfVec3 corner;
 pfSphere::extendBy(box->min);
 corner[0] = box->min[0];  corner[1] = box->min[1];  corner[2] = box->max[2];
 pfSphere::extendBy(corner);
 corner[0] = box->min[0];  corner[1] = box->max[1];  corner[2] = box->min[2];
 pfSphere::extendBy(corner);
 corner[0] = box->min[0];  corner[1] = box->max[1];  corner[2] = box->max[2];
 pfSphere::extendBy(corner);
 corner[0] = box->max[0];  corner[1] = box->min[1];  corner[2] = box->min[2];
 pfSphere::extendBy(corner);
 corner[0] = box->max[0];  corner[1] = box->min[1];  corner[2] = box->max[2];
 pfSphere::extendBy(corner);
 corner[0] = box->max[0];  corner[1] = box->max[1];  corner[2] = box->min[2];
 pfSphere::extendBy(corner);
 pfSphere::extendBy(box->max);
}

void dpfSphere::extendBy(const pfSphere * sph)
{
 pfSphere::extendBy(sph);
}

void dpfSphere::extendBy(const pfCylinder * cyl)
{
 pfSphere::extendBy(cyl);
}

void dpfSphere::around(const pfVec3 * vert,int nvert)
{
 pfSphere::around(vert,nvert);
}

void dpfSphere::around(const pfBox ** boxes,int nboxes)
{
 pfSphere::around(boxes,nboxes);
}

void dpfSphere::around(const pfSphere ** sph,int nsph)
{
 pfSphere::around(sph,nsph);
}

void dpfSphere::around(const pfCylinder ** cyl,int ncyl)
{
 pfSphere::around(cyl,ncyl);
}
