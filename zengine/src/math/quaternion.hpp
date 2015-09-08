#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "vector.hpp"

namespace zengine
{
	class quaternion
	{
	public:
		quaternion(float w, const vector3& v) :w_(w), v_(v){}
		quaternion(const quaternion& q);
		quaternion& operator = (const quaternion& q);

		quaternion crossPrduct(const quaternion& q)const;

		quaternion slerp(const quaternion& q, float t)const;
	public:
		float w_;
		vector3 v_;
	};
}

#endif