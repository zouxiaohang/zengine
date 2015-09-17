#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "model.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include <algorithm>
#include <numeric>

namespace zengine
{
	class window
	{
	public:
		window(int argc, char** argv, const char * title, float width, float height, float fnear = -1, float ffar = 1);
		~window();

		void update();
		void run();

		float width()const{ return width_; }
		float height()const{ return height_; }

		void addModel(modelPtr model){ model_ = model; }
		void setZbuffer(float w, float h, float v);
		void clearZbuffer();

	private:
		void init(int argc, char **argv)const;

	private:
		float width_;
		float height_;
		float near_;
		float far_;
		const char* title_;
		//std::function<void()> display_;
		modelPtr model_;
		float **zbuffer_;
	};
}

#endif