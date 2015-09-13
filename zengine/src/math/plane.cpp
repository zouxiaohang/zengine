#include "plane.hpp"
#include "math_util.hpp"

namespace zengine
{
	plane::plane(const plane& p)
	{
		norm_ = p.norm_;
		point_ = p.point_;
	}

	plane& plane::operator = (const plane& p)
	{
		norm_ = p.norm_;
		point_ = p.point_;
		 
		return *this;
	}

	bool plane::isInPlane(const vector3& p)const
	{
		auto dot = norm_.dotProduct(p - point_);
		return floatEqual(dot, 0.0f);
	}

	bool plane::isInPlane(const line& l)const
	{
		auto dot = norm_.dotProduct(l.dir());
		if (!floatEqual(dot, 0.0f))
			return false;

		return isInPlane(l.start());
	}

	float plane::distance(const vector3& p)const
	{
		if (isInPlane(p))
			return 0.0f;

		return (p - point_).dotProduct(norm_);
	}

	std::pair<bool, vector3> plane::intersection(const line& l)const
	{
		auto ret = std::make_pair<bool, vector3>(false, vector3());
		if (isInPlane(l))
			return ret;

		ret.first = true;
		auto t = (norm_.dotProduct(point_) - norm_.dotProduct(l.start())) / (norm_.dotProduct(l.dir()));
		ret.second = l.start() + t * l.dir();
		return ret;
	}
}