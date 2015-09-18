#include "bmp_loader.hpp"

#include <fstream>
#include <cassert>
#include <iostream>

namespace zengine
{
	vector3 bmp::getPixelColor(int w, int h)const
	{
		vector3 color;
		auto c = data_+ (h * rowPad + w);
		color.x_ = (unsigned char)(*c);
		color.y_ = (unsigned char)(*c + 1);
		color.z_ = (unsigned char)(*c + 2);

		return color;
	}

	bool bmpLoader::load()
	{
		auto ret = false;
		if (path_.empty())
			return ret;

		std::ifstream ifs(path_, std::ifstream::binary);
		if (!ifs)
			return ret;
		fileScoped<std::ifstream> fp(ifs);

		BITMAPFILEHEADER header;
		memset(&header, 0, sizeof(header));
		ifs.read((char *)&header, sizeof(header));
		assert(0x4D42 == header.bfType);

		BITMAPINFOHEADER info;
		memset(&info, 0, sizeof(info));
		ifs.read((char *)&info, sizeof(info));
		assert(info.biBitCount == 24, "the bmp must be  a 24 bits bmp");

		auto width = info.biWidth;
		auto height = info.biHeight;
		int rowPadded = (width * 3 + 3) & (~3);
		auto totalSize = rowPadded * height;

		auto data = new char[totalSize];
		memset(data, 0, totalSize);
		ifs.read((char*)data, totalSize);

		bmp_ = std::make_unique<bmp>();
		bmp_->width_ = width;
		bmp_->height_ = height;
		bmp_->rowPad = rowPadded;
		bmp_->data_ = data;
		ret = true;

		return ret;
	}
}