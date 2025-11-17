#ifndef __dpfSphere_h__
#define __dpfSphere_h__

#include <Performer/pr/pfGeoMath.h>
#include <Performer/pr/pfLinMath.h>
#include "dpfVolume.h"

class dpfSphere : public pfSphere, public dpfVolume
	{
	public:
	 dpfSphere(void);
	 dpfSphere(pfSphere&);
	 virtual float distance(const pfVec3 &);
	 virtual float sqrDistance(const pfVec3 &);
	 virtual int contains(const pfVec3 &);
	 virtual int isect(const pfSeg *,float *,float *);
	 virtual void makeEmpty(void);
	 virtual void extendBy(const pfVec3 &);
	 virtual void extendBy(const pfBox *);
	 virtual void extendBy(const pfSphere *);
	 virtual void extendBy(const pfCylinder *);
	 virtual void around(const pfVec3 *,int);
	 virtual void around(const pfBox **,int);
	 virtual void around(const pfSphere **,int);
	 virtual void around(const pfCylinder **,int);
	protected:
	};

#endif
