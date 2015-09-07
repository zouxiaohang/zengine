#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include <math.h>

namespace zengine
{
#define EPSILON 0.0001f

	bool floatEqual(float f1, float f2)
	{
		if (fabs(f1 - f2) < EPSILON)
			return true;
		return false;
	}
}

#endif