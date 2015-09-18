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
		std::unique_ptr<bmp> getBmp(){ return std::move(bmp_); }

	private:
		std::unique_ptr<bmp> bmp_;
	};
}

#endif