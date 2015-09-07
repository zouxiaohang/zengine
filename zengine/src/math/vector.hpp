#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace zengine
{
	class vector3
	{
	public:
		vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) :x_(x), y_(y), z_(z){}
		vector3(const vector3& v);
		vector3& operator = (const vector3& v);

		void normalize();
		float length()const;

		float dotProduct(const vector3& v)const;
		vector3 crossProduct(const vector3& v)const;

		vector3 operator - ()const{ return vector3(-x_, -y_, -z_); }
	public:
		float x_;
		float y_;
		float z_;
	};

	bool operator == (const vector3& v1, const vector3& v2);
	bool operator != (const vector3& v1, const vector3& v2);
	vector3 operator + (const vector3& v1, const vector3& v2);
	vector3 operator - (const vector3& v1, const vector3& v2);
	vector3 operator * (float k, const vector3& v);
}

#endif