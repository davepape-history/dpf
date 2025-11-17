#ifndef _dpfHermiteCurve_h_
#define _dpfHermiteCurve_h_

#include "dpfCubicCurve.h"

class dpfHermiteCurve : public dpfCubicCurve
	{
	public:
	 dpfHermiteCurve(void);
	 dpfHermiteCurve(pfVec3 point1,pfVec3 point2,pfVec3 dir1,pfVec3 dir2);
	protected:
	 void computeCoefficients(void);
	};

#endif
