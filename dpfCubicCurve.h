#ifndef _dpfCubicCurve_h_
#define _dpfCubicCurve_h_

#include <Performer/pr/pfLinMath.h>

class dpfCubicCurve
	{
	public:
	 dpfCubicCurve(void);
	 dpfCubicCurve(pfVec3,pfVec3,pfVec3,pfVec3);
	 virtual void setControlPoints(pfVec3,pfVec3,pfVec3,pfVec3);
	 virtual pfVec3 value(float t);
	 virtual pfVec3 tangent(float t);
	protected:
	 virtual void computeCoefficients(void);
	 pfVec3 cpt_[4];
	 pfVec4 coeff_[3];
	};

#endif
