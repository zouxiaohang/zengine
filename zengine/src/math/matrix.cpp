#include "matrix.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include <cassert>
#include <math.h>
#include <string.h>

namespace zengine
{
	matrix::matrix()
	{
		memset(mm_, 0, 16 * sizeof(float));
		_11 = _22 = _33 = _44 = 1.0f;
	}

	matrix::matrix(float mat[16])
	{
		_11 = mat[0]; _12 = mat[1]; _13 = mat[2]; _14 = mat[3];
		_21 = mat[4]; _22 = mat[5]; _23 = mat[6]; _24 = mat[7];
		_31 = mat[8]; _32 = mat[9]; _33 = mat[10]; _34 = mat[11];
		_41 = mat[12]; _42 = mat[13]; _43 = mat[14]; _44 = mat[15];
	}

	matrix::matrix(const matrix& mat)
	{
		memcpy(mm_, mat.mm_, 16 * sizeof(float));
	}

	matrix& matrix::operator = (const matrix& mat)
	{
		memcpy(mm_, mat.mm_, 16 * sizeof(float));
		return *this;
	}

	void matrix::identity()
	{
		memset(mm_, 0, 16 * sizeof(float));
		_11 = _22 = _33 = _44 = 1.0f;
	}

	float matrix::determinant()const
	{
		return _11 * (_22 * _33 - _23 * _32) +
			_12 * (_23 * _31 - _21 * _33) +
			_13 * (_21 * _32 - _22 * _31);
	}

	void matrix::inverse()
	{
		auto det = determinant();
		assert(fabs(det) > 0.000001f);

		auto oneOverDet = 1.0f / det;
		auto r = *this;

		_11 = (r._22 * r._33 - r._23 * r._32) * oneOverDet;
		_12 = (r._13 * r._32 - r._12 * r._33) * oneOverDet;
		_13 = (r._12 * r._23 - r._13 * r._22) * oneOverDet;
		_14 = 0.0f;

		_21 = (r._23 * r._31 - r._21 * r._33) * oneOverDet;
		_22 = (r._11 * r._33 - r._13 * r._31) * oneOverDet;
		_23 = (r._13 * r._21 - r._11 * r._23) * oneOverDet;
		_24 = 0.0f;

		_31 = (r._21 * r._32 - r._22 * r._31) * oneOverDet;
		_32 = (r._12 * r._31 - r._11 * r._32) * oneOverDet;
		_33 = (r._11 * r._22 - r._12 * r._21) * oneOverDet;
		_34 = 0.0f;

		_41 = -(r._41 * r._11 + r._42 * r._21 + r._43 * r._31);
		_42 = -(r._41 * r._12 + r._42 * r._22 + r._43 * r._32);
		_43 = -(r._41 * r._13 + r._42 * r._23 + r._43 * r._33);
		_44 = 1.0f;
	}

	void matrix::setScale(const vector3& s)
	{
		identity();
		_11 = s.x_;
		_22 = s.y_;
		_33 = s.z_;
	}

	void matrix::setRotationX(float angle)
	{
		auto cos = cosf(angle);
		auto sin = sinf(angle);
		identity();
		_22 = cos;
		_23 = sin;
		_32 = -sin;
		_33 = cos;
	}

	void matrix::setRotationY(float angle)
	{
		auto cos = cosf(angle);
		auto sin = sinf(angle);
		identity();
		_11 = cos;
		_13 = -sin;
		_31 = sin;
		_33 = cos;
	}

	void matrix::setRotationZ(float angle)
	{
		auto cos = cosf(angle);
		auto sin = sinf(angle);
		identity();
		_11 = cos;
		_12 = sin;
		_21 = -sin;
		_22 = cos;
	}

	void matrix::setTranslation(const vector3& t)
	{
		identity();
		_41 = t.x_;
		_42 = t.y_;
		_43 = t.z_;
	}

	void matrix::fromQuaternion(const quaternion& q)
	{
		auto ww = 2.0f * q.w_;
		auto xx = 2.0f * q.v_.x_;
		auto yy = 2.0f * q.v_.y_;
		auto zz = 2.0f * q.v_.z_;

		_11 = 1.0f - yy * q.v_.y_ - zz * q.v_.z_;
		_12 = xx * q.v_.y_ + ww * q.v_.z_;
		_13 = xx * q.v_.z_ - ww * q.v_.x_;
		_14 = 0.0f;

		_21 = xx * q.v_.y_ - ww * q.v_.z_;
		_22 = 1.0f - xx * q.v_.x_ - zz * q.v_.z_;
		_23 = yy * q.v_.z_ + ww * q.v_.x_;
		_24 = 0.0f;

		_31 = xx * q.v_.z_ + ww * q.v_.y_;
		_32 = yy * q.v_.z_ - ww * q.v_.x_;
		_33 = 1.0f - xx * q.v_.x_ - yy * q.v_.y_;
		_34 = 0.0f;

		_41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
	}

	quaternion matrix::toQuaternion()const
	{
		quaternion q(0.0f, vector3());

		q.w_ = sqrtf(_11 + _22 + _33 + 1) / 2;
		q.v_.x_ = (_23 - _32) / (4 * q.w_);
		q.v_.y_ = (_31 - _13) / (4 * q.w_);
		q.v_.z_ = (_12 - _21) / (4 * q.w_);

		return q;
	}

	vector4 matrix::applyVector4(const vector4& v)
	{
		vector4 ret;
		ret.x_ = v.x_ * _11 + v.y_ * _21 + v.z_ * _31 + v.w_ * _41;
		ret.y_ = v.x_ * _12 + v.y_ * _22 + v.z_ * _32 + v.w_ * _42;
		ret.z_ = v.x_ * _13 + v.y_ * _23 + v.z_ * _33 + v.w_ * _43;
		ret.w_ = v.x_ * _14 + v.y_ * _24 + v.z_ * _34 + v.w_ * _44;
		return ret;
	}

	matrix operator *(float s, const matrix& mat)
	{
		matrix ret;
		ret._11 = mat._11 * s; ret._12 = mat._12 * s; ret._13 = mat._13 * s; ret._14 = mat._14 * s;
		ret._21 = mat._21 * s; ret._22 = mat._22 * s; ret._23 = mat._23 * s; ret._24 = mat._24 * s;
		ret._31 = mat._31 * s; ret._32 = mat._32 * s; ret._33 = mat._33 * s; ret._34 = mat._34 * s;
		ret._41 = mat._41 * s; ret._42 = mat._42 * s; ret._43 = mat._43 * s; ret._44 = mat._44 * s;

		return ret;
	}

	matrix operator *(const matrix& m1, const matrix& m2)
	{
		matrix ret;
		ret._11 = m1._11 * m2._11 + m1._12 * m2._21 + m1._13 * m2._31 + m1._14 * m2._41;
		ret._12 = m1._11 * m2._12 + m1._12 * m2._22 + m1._13 * m2._32 + m1._14 * m2._42;
		ret._13 = m1._11 * m2._13 + m1._12 * m2._23 + m1._13 * m2._33 + m1._14 * m2._43;
		ret._14 = m1._11 * m2._14 + m1._12 * m2._24 + m1._13 * m2._34 + m1._14 * m2._44;

		ret._21 = m1._21 * m2._11 + m1._22 * m2._21 + m1._23 * m2._31 + m1._24 * m2._41;
		ret._22 = m1._21 * m2._12 + m1._22 * m2._22 + m1._23 * m2._32 + m1._24 * m2._42;
		ret._23 = m1._21 * m2._13 + m1._22 * m2._23 + m1._23 * m2._33 + m1._24 * m2._43;
		ret._24 = m1._21 * m2._14 + m1._22 * m2._24 + m1._23 * m2._34 + m1._24 * m2._44;

		ret._31 = m1._31 * m2._11 + m1._32 * m2._21 + m1._33 * m2._31 + m1._34 * m2._41;
		ret._32 = m1._31 * m2._12 + m1._32 * m2._22 + m1._33 * m2._32 + m1._34 * m2._42;
		ret._33 = m1._31 * m2._13 + m1._32 * m2._23 + m1._33 * m2._33 + m1._34 * m2._43;
		ret._34 = m1._31 * m2._14 + m1._32 * m2._24 + m1._33 * m2._34 + m1._34 * m2._44;

		ret._41 = m1._41 * m2._11 + m1._42 * m2._21 + m1._43 * m2._31 + m1._44 * m2._41;
		ret._42 = m1._41 * m2._12 + m1._42 * m2._22 + m1._43 * m2._32 + m1._44 * m2._42;
		ret._43 = m1._41 * m2._13 + m1._42 * m2._23 + m1._43 * m2._33 + m1._44 * m2._43;
		ret._44 = m1._41 * m2._14 + m1._42 * m2._24 + m1._43 * m2._34 + m1._44 * m2._44;

		return ret;
	}
}