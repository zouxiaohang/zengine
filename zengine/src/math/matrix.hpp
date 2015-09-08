#ifndef _MATRIX_H_
#define _MATRIX_H_

namespace zengine
{
	class vector3;
	class vector4;

	class matrix
	{
	public:
		matrix();
		matrix(float mat[16]);
		matrix(const matrix& mat);
		matrix& operator = (const matrix& mat);

		void row(int r, const vector4& v);
		vector4 row(int r)const;

		void identity();

		void setScale(const vector3& s);
		void setRotationX(float angle);
		void setRotationY(float angle);
		void setRotationZ(float angle);
		void setTranslation(const vector3& t);

		vector4 applyVector4(const vector4& v);
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