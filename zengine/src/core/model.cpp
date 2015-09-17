#include "model.hpp"
#include "../math/matrix.hpp"

namespace zengine
{
	model::model(const verticeArrayType& v) :vertices_(v)
	{
	}

	void model::transform(const matrix& tm, transformType type)
	{
		switch (type)
		{
		case WORLD_TRANSFORM:
			for (const auto& v : vertices_)
			{
				modelWorld_.emplace_back(tm.applyVector4(vector4(v, 1.0f)));
			}
			break;
		case VIEW_TRANDFORM:
			for (const auto& v : modelWorld_)
			{
				modelView_.emplace_back(tm.applyVector4(v));
			}
			break;
		case WORLD_VIEW_TRANSFORM:
			for (const auto& v : vertices_)
			{
				modelView_.emplace_back(tm.applyVector4(vector4(v, 1.0f)));
			}
			break;
		case PROJECTION_TRANSFORM:
			for (const auto& v : modelView_)
			{
				auto v4 = tm.applyVector4(v);
				v4.homogeneous();
				modelProj_.emplace_back(v4);
			}
			break;
		case WORLD_VIEW_PROJECT_TRANSFORM:
			for (const auto& v : vertices_)
			{
				auto v4 = vector4(v, 1.0f);
				v4 = tm.applyVector4(v4);//to clip space
				//v4.homogeneous();//to NDC space
				modelProj_.emplace_back(v4);
			}
			break;
		default:
			break;
		}
	}

	void model::transformToNDC()
	{
		for (const auto& v : modelProj_)
		{
			auto v4 = v;
			v4.homogeneous();
			modelNDC_.emplace_back(v4);
		}
	}

	void model::transformToScreen(float width, float heigth)
	{
		modelScreen_.resize(modelProj_.size());
		for (int i = 0; i != modelProj_.size(); ++i)
		{
			const auto& point = modelProj_[i];
			// screen:
			//  (0,0)------------------>x
			//		|
			//		|
			//		|
			//		|
			//	   y\/

			// x - (-1)     x'
			//---------- = -----------
			// 1 - (-1)     width - 1
			modelScreen_[i].x_ = ((point.x_ + 1) / 2) * (width - 1);
			// 1 - y		y'
			//---------- = ------------  ps: screen in y is inverse, so we write:(1 - y)
			// 1 - (-1)		height - 1
			modelScreen_[i].y_ = ((1 - point.y_) / 2) * (heigth - 1);
			modelScreen_[i].z_ = point.z_;
		}
	}

	void model::clear()
	{
		modelWorld_.clear();
		modelView_.clear();
		modelProj_.clear(); 
		modelNDC_.clear();
		modelScreen_.clear();
	}
}