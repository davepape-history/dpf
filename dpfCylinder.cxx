#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "dpfCylinder.h"

dpfCylinder::dpfCylinder(void)
{
 pfCylinder::makeEmpty();
}

dpfCylinder::dpfCylinder(pfCylinder & cyl)
{
 pfCylinder::center = cyl.center;
 pfCylinder::radius = cyl.radius;
 pfCylinder::axis = cyl.axis;
 pfCylinder::halfLength = cyl.halfLength;
}


float dpfCylinder::sqrDistance(const pfVec3 & v)
{
 pfVec3 vRelative, vProj;
 float projLength;
 vRelative = v - center;
 projLength = vRelative.dot(axis);
 vProj = axis * projLength;
 if (fabs(projLength) <= halfLength)
	{
	float dist = vRelative.distance(vProj) - radius;
	return dist * dist;
	}
 else
	{
	pfVec3 capCenter, dirToV, nearestPoint;
	if (projLength > 0)
		capCenter = halfLength * axis;
	else
		capCenter = -halfLength * axis;
	dirToV = vRelative - vProj;
	if (dirToV.dot(dirToV) > radius*radius)
		{
		dirToV.normalize();
		nearestPoint = capCenter + radius * dirToV;
		}
	else
		nearestPoint = capCenter + dirToV;
	return vRelative.sqrDistance(nearestPoint);
	}
}


int dpfCylinder::contains(const pfVec3 &v)
{
 return pfCylinder::contains(v);
}

int dpfCylinder::isect(const pfSeg *s,float *d0,float *d1)
{
 return pfCylinder::isect(s,d0,d1);
}

void dpfCylinder::makeEmpty(void)
{
 pfCylinder::makeEmpty();
}

void dpfCylinder::extendBy(const pfVec3 & v)
{
 pfCylinder::extendBy(v);
}

void dpfCylinder::extendBy(const pfBox * box)
{
 pfVec3 corner;
 pfCylinder::extendBy(box->min);
 corner[0] = box->min[0];  corner[1] = box->min[1];  corner[2] = box->max[2];
 pfCylinder::extendBy(corner);
 corner[0] = box->min[0];  corner[1] = box->max[1];  corner[2] = box->min[2];
 pfCylinder::extendBy(corner);
 corner[0] = box->min[0];  corner[1] = box->max[1];  corner[2] = box->max[2];
 pfCylinder::extendBy(corner);
 corner[0] = box->max[0];  corner[1] = box->min[1];  corner[2] = box->min[2];
 pfCylinder::extendBy(corner);
 corner[0] = box->max[0];  corner[1] = box->min[1];  corner[2] = box->max[2];
 pfCylinder::extendBy(corner);
 corner[0] = box->max[0];  corner[1] = box->max[1];  corner[2] = box->min[2];
 pfCylinder::extendBy(corner);
 pfCylinder::extendBy(box->max);
}

void dpfCylinder::extendBy(const pfSphere * sph)
{
 pfCylinder::extendBy(sph);
}

void dpfCylinder::extendBy(const pfCylinder * cyl)
{
 pfCylinder::extendBy(cyl);
}

void dpfCylinder::around(const pfVec3 * vert,int nvert)
{
 pfCylinder::around(vert,nvert);
}

void dpfCylinder::around(const pfBox ** boxes,int nboxes)
{
 pfCylinder::around(boxes,nboxes);
}

void dpfCylinder::around(const pfSphere ** sph,int nsph)
{
 pfCylinder::around(sph,nsph);
}

void dpfCylinder::around(const pfCylinder ** cyl,int ncyl)
{
 int i;
 pfCylinder::makeEmpty();
 for (i=0; i < ncyl; i++)
	pfCylinder::extendBy(cyl[i]);
}
