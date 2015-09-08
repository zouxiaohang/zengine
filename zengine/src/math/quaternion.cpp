#include "quaternion.hpp"

#include <math.h>

namespace zengine
{
	quaternion::quaternion(const quaternion& q)
	{
		w_ = q.w_;
		v_ = q.w_;
	}

	quaternion& quaternion::operator = (const quaternion& q)
	{
		w_ = q.w_;
		v_ = q.v_;
		return *this;
	}

	quaternion quaternion::crossPrduct(const quaternion& q)const
	{
		return quaternion(w_ * q.w_ - v_.dotProduct(q.v_),
			w_ * q.v_ + q.w_ * v_ + q.v_.crossProduct(v_));
	}

	quaternion quaternion::slerp(const quaternion& q, float t)const
	{
		auto cosOmega = w_ * q.w_ + v_.dotProduct(q.v_);
		auto tempQ = q;
		if (cosOmega < 0.0f)
		{
			tempQ.w_ = tempQ.w_;
			tempQ.v_ = -tempQ.v_;
			cosOmega = -cosOmega;
		}
		float k0, k1;
		if (cosOmega > 0.9999f)
		{
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{
			auto sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
			auto omega = atan2f(sinOmega, cosOmega);
			k0 = sinf((1.0f - t) * omega) / sinOmega;
			k1 = sinf(t * omega) / sinOmega;
		}

		return quaternion(w_ * k0 + q.w_ * k1, 
			vector3(v_.x_ * k0 + q.v_.x_ * k1,
			v_.y_ * k0 + q.v_.y_ * k1, 
			v_.z_ * k0 + q.v_.z_ * k1));
	}
}