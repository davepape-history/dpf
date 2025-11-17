#ifndef _dpfBsplineCurve_h_
#define _dpfBsplineCurve_h_

#include "dpfCubicCurve.h"

class dpfBsplineCurve : public dpfCubicCurve
	{
	public:
	 dpfBsplineCurve(void);
	 dpfBsplineCurve(pfVec3,pfVec3,pfVec3,pfVec3);
	protected:
	 void computeCoefficients(void);
	};

#endif
