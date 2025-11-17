#ifndef _dpfBezierCurve_h_
#define _dpfBezierCurve_h_

#include "dpfCubicCurve.h"

class dpfBezierCurve : public dpfCubicCurve
	{
	public:
	 dpfBezierCurve(void);
	 dpfBezierCurve(pfVec3,pfVec3,pfVec3,pfVec3);
	protected:
	 void computeCoefficients(void);
	};

#endif
