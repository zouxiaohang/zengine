#ifndef _LINE_H_
#define _LINE_H_

#include "vector.hpp"

namespace zengine
{
	class line
	{
	public:
		line(const vector3& start, const vector3& dir) :start_(start), dir_(dir){ dir_.normalize(); }
		line(const line& l);
		line& operator = (const line& l);

		float distance(const vector3& v)const;
		float distance(const line& l)const;

		bool isParallel(const line& l)const;
		bool isInLine(const vector3& p)const;

		const vector3& dir()const{ return dir_; }
		const vector3& start()const{ return start_; }
	private:
		vector3 start_;
		vector3 dir_;//unit vector
	};
}

#endif