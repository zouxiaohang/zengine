#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_


#define _USE_MATH_DEFINES
#include <math.h>

namespace zengine
{
#define EPSILON 0.0001f
#define PI M_PI

	inline bool floatEqual(float f1, float f2)
	{
		if (fabs(f1 - f2) < EPSILON)
			return true;
		return false;
	}

	inline float angleToRadian(float angle)
	{
		return angle * PI / 180.0f;
	}

	inline float radianToAngle(float radian)
	{
		return 180.0f * radian / PI;
	}
}

#endif