#ifndef __dpfVolume_h__
#define __dpfVolume_h__

#include <Performer/pr/pfLinMath.h>
#include <Performer/pr/pfGeoMath.h>

class dpfVolume
	{
	public:
	 dpfVolume(void);
	 virtual float distance(const pfVec3 &v);
	 virtual float sqrDistance(const pfVec3 &)=0;
	 virtual int contains(const pfVec3 &)=0;
	 virtual int isect(const pfSeg *,float *,float *)=0;
	 virtual void makeEmpty(void)=0;
	 virtual void extendBy(const pfVec3 &)=0;
	 virtual void extendBy(const pfBox *)=0;
	 virtual void extendBy(const pfSphere *)=0;
	 virtual void extendBy(const pfCylinder *)=0;
	 virtual void around(const pfVec3 *,int)=0;
	 virtual void around(const pfBox **,int)=0;
	 virtual void around(const pfSphere **,int)=0;
	 virtual void around(const pfCylinder **,int)=0;
	protected:
	};

#endif
