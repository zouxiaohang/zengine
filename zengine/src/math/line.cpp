#include "line.hpp"
#include "math_util.hpp"

namespace zengine
{
	line::line(const line& l)
	{
		start_ = l.start_;
		dir_ = l.dir_;
	}

	line& line::operator = (const line& l)
	{
		start_ = l.start_;
		dir_ = l.dir_;

		return *this;
	}

	bool line::isParallel(const line& l)const
	{
		auto dot = dir_.dotProduct(l.dir_);
		return floatEqual(dot, 0.0f);
	}

	bool line::isInLine(const vector3& p)const
	{
		auto dir = p - start_;
		return isParallel(line(start_, dir));
	}

	float line::distance(const vector3& v)const
	{
		auto ll = v - start_;
		auto llLength = ll.length();
		auto t = ll.dotProduct(dir_);
		
		return sqrtf(llLength * llLength - t * t);
	}

	float line::distance(const line& l)const
	{
		if (isParallel(l))
			return distance(l.start_);

		auto v1v2 = dir_.dotProduct(l.dir_);
		auto oneOverv1v1 = 1.0f / (dir_.dotProduct(l.dir_) - 1);
		auto s2s1v1 = (l.start_ - start_).dotProduct(dir_);
		auto s2s1v2 = (l.start_ - start_).dotProduct(l.dir_);

		auto t1 = -s2s1v1 + s2s1v2 * v1v2 * oneOverv1v1;
		auto t2 = -s2s1v1 * v1v2 + s2s1v2 * oneOverv1v1;

		return ((start_ + t1 * dir_) - (l.start_ + t2 * l.dir_)).length();
	}
}