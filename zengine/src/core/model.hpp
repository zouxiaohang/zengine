#ifndef _MODEL_H_
#define _MODEL_H_

#include "../math/vector.hpp"
#include "../file/bmp_loader.hpp"

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
	private:
		struct tc_tag
		{
			tc_tag(float u, float v):u_(u), v_(v){}
			float u_; 
			float v_;
		};
	public:
		using verticeType = vector3;
		using verticeArrayType = std::vector<verticeType>;
		using verticePositionArray = std::vector<vector4>;

		using textureCoordType = tc_tag;
		using textureCoordArrayType = std::vector<textureCoordType>;
	public:
		model(const verticeArrayType& v, const textureCoordArrayType& tc);

		void transform(const matrix& tm, transformType type);
		void transformToNDC();
		void transformToScreen(float width, float height);

		verticePositionArray modelInNDC()const{ return modelNDC_; }
		verticeArrayType modelInScreen()const{ return modelScreen_; }

		textureCoordArrayType modelTextureCoord()const{ return textureCoords_; }

		void addBmpTexture(bmpPtr bmp){ bmpTexture_ = bmp; }
		bmpPtr getBmpTexture(){ return bmpTexture_; }

		void clear();

	private:
		verticeArrayType vertices_;
		verticePositionArray modelWorld_;
		verticePositionArray modelView_;
		verticePositionArray modelProj_;
		verticePositionArray modelNDC_;
		verticeArrayType modelScreen_;

		bmpPtr bmpTexture_;
		textureCoordArrayType textureCoords_;
	};

	using modelPtr = std::shared_ptr<model>;
}

#endif