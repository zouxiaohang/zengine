#ifndef _PLANE_H_
#define _PLANE_H_

#include "line.hpp"

#include <utility>

namespace zengine
{
	class plane
	{
	public:
		plane(const vector3& point, const vector3& norm) :point_(point), norm_(norm){ norm_.normalize(); }
		plane(const plane& p);
		plane& operator = (const plane& p);

		bool isInPlane(const vector3& p)const;
		bool isInPlane(const line& l)const;

		float distance(const vector3& p)const;
		std::pair<bool, vector3> intersection(const line& l)const;
	private:
		vector3 norm_;
		vector3 point_;
	};
}

#endif