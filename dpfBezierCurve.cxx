#include <stdio.h>
#include <math.h>
#include "dpfBezierCurve.h"

dpfBezierCurve::dpfBezierCurve(void)
{
}

dpfBezierCurve::dpfBezierCurve(pfVec3 p0,pfVec3 p1,pfVec3 p2,pfVec3 p3) :
	dpfCubicCurve(p0,p1,p2,p3)
{
}

void dpfBezierCurve::computeCoefficients(void)
{
 pfMatrix Bezier ( -1,  3, -3,  1,
		    3, -6,  3,  0,
		   -3,  3,  0,  0,
		    1,  0,  0,  0 );
 pfVec4 geom;
 geom.set(cpt_[0][0], cpt_[1][0], cpt_[2][0], cpt_[3][0]);
 coeff_[0].xform(geom,Bezier);
 geom.set(cpt_[0][1], cpt_[1][1], cpt_[2][1], cpt_[3][1]);
 coeff_[1].xform(geom,Bezier);
 geom.set(cpt_[0][2], cpt_[1][2], cpt_[2][2], cpt_[3][2]);
 coeff_[2].xform(geom,Bezier);
}
