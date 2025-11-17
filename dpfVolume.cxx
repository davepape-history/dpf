#include <math.h>
#include "dpfVolume.h"


dpfVolume::dpfVolume(void)
{
}

float dpfVolume::distance(const pfVec3 &v)
{
 return fsqrt(sqrDistance(v));
}
