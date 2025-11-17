#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "dpfPoint.h"

dpfPoint::dpfPoint(void)
{
 vec[0] = vec[1] = vec[2] = 0.0f;
}

dpfPoint::dpfPoint(pfVec3 & v)
{
 vec[0] = v[0];
 vec[1] = v[1];
 vec[2] = v[2];
}


float dpfPoint::sqrDistance(const pfVec3 & v)
{
 return pfVec3::sqrDistance(v);
}


int dpfPoint::contains(const pfVec3 &v)
{
 if (equal(v))
	return PFIS_MAYBE|PFIS_TRUE|PFIS_ALL_IN;
 else
	return PFIS_FALSE;
}

int dpfPoint::isect(const pfSeg *s,float *d0,float *d1)
{
 pfVec3 dirToPoint;
 float distToPoint;
 dirToPoint = *this - s->pos;
 distToPoint = s->dir.dot(dirToPoint);
 if ((distToPoint >= 0.0f) && (distToPoint <= s->length))
	{
	if (d0)
		*d0 = distToPoint;
	if (d1)
		*d1 = distToPoint;
	if (s->length == 0.0f)
		return PFIS_MAYBE|PFIS_TRUE|PFIS_START_IN|PFIS_END_IN|PFIS_ALL_IN;
	else if (distToPoint == 0.0f)
		return PFIS_MAYBE|PFIS_TRUE|PFIS_START_IN;
	else if (distToPoint == s->length)
		return PFIS_MAYBE|PFIS_TRUE|PFIS_END_IN;
	else
		return PFIS_MAYBE|PFIS_TRUE;
	}
 else
	return PFIS_FALSE;
}

void dpfPoint::makeEmpty(void)
{
 vec[0] = vec[1] = vec[2] = 0.0f;
}

void dpfPoint::extendBy(const pfVec3 & v)
{
 vec[0] = v[0];
 vec[1] = v[1];
 vec[2] = v[2];
}

void dpfPoint::extendBy(const pfBox * box)
{
 pfVec3 center;
 center = (box->min + box->max) / 2;
 vec[0] = center[0];
 vec[1] = center[1];
 vec[2] = center[2];
}

void dpfPoint::extendBy(const pfSphere * sph)
{
 vec[0] = sph->center[0];
 vec[1] = sph->center[1];
 vec[2] = sph->center[2];
}

void dpfPoint::extendBy(const pfCylinder * cyl)
{
 vec[0] = cyl->center[0];
 vec[1] = cyl->center[1];
 vec[2] = cyl->center[2];
}

void dpfPoint::around(const pfVec3 * vert,int nvert)
{
 if (nvert > 0)
	extendBy(vert[0]);
}

void dpfPoint::around(const pfBox ** boxes,int nboxes)
{
 if (nboxes > 0)
	extendBy(boxes[0]);
}

void dpfPoint::around(const pfSphere ** sph,int nsph)
{
 if (nsph > 0)
	extendBy(sph[0]);
}

void dpfPoint::around(const pfCylinder ** cyl,int ncyl)
{
 if (ncyl > 0)
	extendBy(cyl[0]);
}
