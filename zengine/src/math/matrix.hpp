#ifndef _MATRIX_H_
#define _MATRIX_H_

namespace zengine
{
	class vector3;
	class vector4;
	class quaternion;

	class matrix
	{
	public:
		matrix();
		matrix(float mat[16]);
		matrix(const matrix& mat);
		matrix& operator = (const matrix& mat);

		void identity();
		float determinant()const;
		void inverse();

		void setScale(const vector3& s);
		void setRotationX(float angle);
		void setRotationY(float angle);
		void setRotationZ(float angle);
		void setTranslation(const vector3& t);

		void fromQuaternion(const quaternion& q);
		quaternion toQuaternion()const;

		vector4 applyVector4(const vector4& v);

		void setLookAtLH(const vector3& eye, const vector3& at, const vector3& up);
		void setPerspectiveLH(float w, float h, float zn, float zf);
		void setPerspectiveFovLH(float fovy, float aspect, float zn, float zf);
	public:
		union
		{
			float mm_[4][4];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};
	};

	matrix operator *(float s, const matrix& mat);
	matrix operator *(const matrix& m1, const matrix& m2);
}

#endif