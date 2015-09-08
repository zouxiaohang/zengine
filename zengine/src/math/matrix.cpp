#include "matrix.hpp"
#include "vector.hpp"

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