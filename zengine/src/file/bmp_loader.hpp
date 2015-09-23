#ifndef _BMP_LOADER_H_
#define _BMP_LOADER_H_

#include "image_loader.hpp"
#include "../math/vector.hpp"

#include <memory>

#include <Windows.h>

namespace zengine
{
	class bmp
	{
	public:
		vector3 getPixelColor(int w, int h)const;

	public:
		const char * data_;
		size_t width_;
		size_t height_;
		size_t rowPad;
	};

	class bmpLoader : public imageLoader
	{
	public:
		explicit bmpLoader(const std::string& path) :imageLoader(path){}
		virtual ~bmpLoader(){}

		virtual bool load();
		std::shared_ptr<bmp> getBmp(){ return bmp_; }

	private:
		std::shared_ptr<bmp> bmp_;
	};

	using bmpPtr = std::shared_ptr<bmp>;
}

#endif