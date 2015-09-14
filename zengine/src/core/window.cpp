#include "window.hpp"

namespace zengine
{
	void window::init(int argc, char **argv)const
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(width_, height_);
		glutInitWindowPosition(400, 250);
		glutCreateWindow(title_);

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glLoadIdentity();
		glOrtho(0, width_, 0, height_, near_, far_);
	}

	void window::run(void(*display)(void))
	{
		glutDisplayFunc(display);
		glutMainLoop();
	}
}