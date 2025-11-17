#ifndef _dpfCatmullRomCurve_h_
#define _dpfCatmullRomCurve_h_

#include "dpfCubicCurve.h"

class dpfCatmullRomCurve : public dpfCubicCurve
	{
	public:
	 dpfCatmullRomCurve(void);
	 dpfCatmullRomCurve(pfVec3,pfVec3,pfVec3,pfVec3);
	protected:
	 void computeCoefficients(void);
	};

#endif
