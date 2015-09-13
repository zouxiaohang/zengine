#include<iostream>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include "src\math\vector.hpp"
#include "src\math\matrix.hpp"
#include "src\math\math_util.hpp"

#include <DirectXMath.h>

using namespace std;

const int MODELSIZE = 4;
zengine::vector3 cubeModel[MODELSIZE] = {
	//{0,0,0},
	//{3, 0, 0},
	//{0, 3, 0}
	{ 10, 10, 10 },
	{ -10, 10, 10 },
	//{ -10, 10, -10 },
	//{ 10, 10, -10 },
	{ 10, -10, 10 },
	{ -10, -10, 10 },
	//{ -10, -10, -10 },
	//{ 10, -10, -10 }
};

zengine::vector4 cubeWorld[MODELSIZE];
zengine::vector4 cubeView[MODELSIZE];
zengine::vector4 cubeProj[MODELSIZE];
zengine::vector4 cubeNDC[MODELSIZE];

namespace
{
	void init(void)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glLoadIdentity();
		glOrtho(0, 640, 0, 360, -1, 1);
	}
	void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2f(0.4f, 0.5f);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (auto& p : cubeNDC)
		{
			auto point = p;
			point.x_ = ((point.x_ + 1) / 2) * 640;
			point.y_ = ((1 - point.y_) / 2) * 360;
			cout << point.x_ << " " << point.y_ << " " << point.z_ << endl;
			glVertex2f(point.x_, point.y_);
		}
		glEnd();
		glFlush();
	}
}

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	zengine::matrix worldTransform;
	worldTransform.setTranslation(zengine::vector3(1, 1, 0));
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeWorld[i] = worldTransform.applyVector4(zengine::vector4(cubeModel[i], 1.0f));
	}

	
	zengine::matrix viewTransform;
	zengine::vector3 eye(0, 0, -10);
	zengine::vector3 focus(0, 0, 0);
	zengine::vector3 up(0, 1, 0);
	viewTransform.setLookAtLH(eye, focus, up);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeView[i] = viewTransform.applyVector4(cubeWorld[i]);
	}
	
	zengine::matrix projTransform;
	projTransform.setPerspectiveFovLH(zengine::angleToRadian(90), 640.0f / 360, 0.1f, 1.0f);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeProj[i] = projTransform.applyVector4(cubeView[i]);
	}

	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeNDC[i] = cubeProj[i];
		//NDC
		cubeNDC[i].homogeneous();
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 360); 
	glutInitWindowPosition(400, 250);
	glutCreateWindow("hello zengine");
	init();
	glutDisplayFunc(display); 
	glutMainLoop();

	system("pause");
	return 0;
}

