#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "model.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

//#include <functional>

namespace zengine
{
	class window
	{
	public:
		window(int argc, char** argv, const char * title, float width, float height, float fnear = -1, float ffar = 1):
			width_(width), height_(height), near_(fnear), far_(ffar), title_(title)
		{
			init(argc, argv);
		}

		void update();
		void run();

		float width()const{ return width_; }
		float height()const{ return height_; }

		void addModel(modelPtr model){ model_ = model; }

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
	};
}

#endif