#include <stdio.h>
#include <math.h>
#include "dpfCubicCurve.h"

dpfCubicCurve::dpfCubicCurve(void)
{
 cpt_[0].set(0,0,0);
 cpt_[1].set(0,0,0);
 cpt_[2].set(0,0,0);
 cpt_[3].set(0,0,0);
 coeff_[0].set(0,0,0,0);
 coeff_[1].set(0,0,0,0);
 coeff_[2].set(0,0,0,0);
}

dpfCubicCurve::dpfCubicCurve(pfVec3 p0,pfVec3 p1,pfVec3 p2,pfVec3 p3)
{
 cpt_[0] = p0;
 cpt_[1] = p1;
 cpt_[2] = p2;
 cpt_[3] = p3;
 computeCoefficients();
}

void dpfCubicCurve::setControlPoints(pfVec3 p0,pfVec3 p1,pfVec3 p2,pfVec3 p3)
{
 cpt_[0] = p0;
 cpt_[1] = p1;
 cpt_[2] = p2;
 cpt_[3] = p3;
 computeCoefficients();
}

void dpfCubicCurve::computeCoefficients(void)
{
 int v;
 for (v=0; v<3; v++)
	coeff_[v].set(0,0,cpt_[3][v]-cpt_[0][v],cpt_[0][v]);
}

pfVec3 dpfCubicCurve::value(float t)
{
 pfVec4 T;
 pfVec3 val;
 T.set(t*t*t,t*t,t,1.0f);
 val[0] = T.dot(coeff_[0]);
 val[1] = T.dot(coeff_[1]);
 val[2] = T.dot(coeff_[2]);
 return val;
}

pfVec3 dpfCubicCurve::tangent(float t)
{
 pfVec4 T;
 pfVec3 val;
 T.set(3.0f*t*t,2.0f*t,1.0f,0.0f);
 val[0] = T.dot(coeff_[0]);
 val[1] = T.dot(coeff_[1]);
 val[2] = T.dot(coeff_[2]);
 return val;
}
