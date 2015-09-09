#include "vector.hpp"
#include "math_util.hpp"

#include <math.h>

namespace zengine
{
	//******************  vector3 **********************
	vector3::vector3(const vector3& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	vector3& vector3::operator = (const vector3& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		return *this;
	}

	float vector3::length()const
	{
		auto len = x_ * x_ + y_ * y_ + z_ * z_;
		return sqrtf(len);
	}

	void vector3::normalize()
	{
		auto len = length();
		auto reciprocal = 1.0f / len;
		
		x_ *= reciprocal;
		y_ *= reciprocal;
		z_ *= reciprocal;
	}

	float vector3::dotProduct(const vector3& v)const
	{
		return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
	}

	vector3 vector3::crossProduct(const vector3& v)const
	{
		return vector3(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
	}

	//v' = (this) * (1 - t) + v * t
	vector3 vector3::lerp(const vector3& v, float t)
	{
		return vector3(x_ * (1 - t) + t * v.x_,
			y_ * (1 - t) + t * v.y_,
			z_ * (1 - t) + t * v.z_);
	}

	bool operator == (const vector3& v1, const vector3& v2)
	{
		return floatEqual(v1.x_, v2.x_) && floatEqual(v1.y_, v2.y_) && floatEqual(v1.z_, v2.z_);
	}
	bool operator != (const vector3& v1, const vector3& v2)
	{
		return !(v1 == v2);
	}
	vector3 operator + (const vector3& v1, const vector3& v2)
	{
		return vector3(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
	}
	vector3 operator - (const vector3& v1, const vector3& v2)
	{
		return vector3(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
	}
	vector3 operator * (float k, const vector3& v)
	{
		return vector3(k * v.x_, k * v.y_, k * v.z_);
	}

	//******************  vector4 **********************
	vector4::vector4(const vector4& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		w_ = v.w_;
	}

	vector4::vector4(const vector3& v, float w)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		w_ = w;
	}

	vector4& vector4::operator = (const vector4& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		w_ = v.w_;

		return *this;
	}

	void vector4::normalize()
	{
		auto len = length();

		x_ /= len;
		y_ /= len;
		z_ /= len;
		w_ /= len;
	}

	float vector4::length()const
	{
		return sqrtf(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);;
	}
}