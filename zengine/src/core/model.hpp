#ifndef _MODEL_H_
#define _MODEL_H_

#include "../math/vector.hpp"

#include <memory>
#include <vector>

namespace zengine
{
	class matrix; 

	class model
	{
	public:
		enum transformType
		{
			WORLD_TRANSFORM = 0,
			VIEW_TRANDFORM,
			WORLD_VIEW_TRANSFORM,
			PROJECTION_TRANSFORM,
			WORLD_VIEW_PROJECT_TRANSFORM,
		};
	public:
		using verticeType = vector3;
		using verticeArrayType = std::vector<verticeType>;
		using verticePositionArray = std::vector<vector4>;
	public:
		explicit model(const verticeArrayType& v);

		void transform(const matrix& tm, transformType type);
		void transformToNDC();
		void transformToScreen(float width, float height);

		verticePositionArray modelInNDC()const{ return modelNDC_; }
		verticeArrayType modelInScreen()const{ return modelScreen_; }

		void clear();

	private:
		verticeArrayType vertices_;
		verticePositionArray modelWorld_;
		verticePositionArray modelView_;
		verticePositionArray modelProj_;
		verticePositionArray modelNDC_;
		verticeArrayType modelScreen_;
	};

	using modelPtr = std::shared_ptr<model>;
}

#endif