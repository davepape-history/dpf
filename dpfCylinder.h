#ifndef __dpfCylinder_h__
#define __dpfCylinder_h__

#include <Performer/pr/pfGeoMath.h>
#include <Performer/pr/pfLinMath.h>
#include "dpfVolume.h"

class dpfCylinder : public pfCylinder, public dpfVolume
	{
	public:
	 dpfCylinder(void);
	 dpfCylinder(pfCylinder&);
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
