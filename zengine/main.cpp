#include<iostream>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include "src\math\vector.hpp"
#include "src\math\matrix.hpp"
#include "src\math\math_util.hpp"

#include <DirectXMath.h>

using namespace std;

const int MODELSIZE = 8;
zengine::vector3 cubeModel[MODELSIZE] = {
	//{1,1,1},
	//{5, 1, 1},
	//{1, 5, 1}
	{ 10, 10, 10 },
	{ -10, 10, 10 },
	{ -10, 10, -10 },
	{ 10, 10, -10 },
	{ 10, -10, 10 },
	{ -10, -10, 10 },
	{ -10, -10, -10 },
	{ 10, -10, -10 }
};

zengine::vector4 cubeWorld[MODELSIZE];
zengine::vector4 cubeView[MODELSIZE];
zengine::vector4 cubeProj[MODELSIZE];
zengine::vector4 cubeScreen[MODELSIZE];

namespace
{
	void init(void)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}
	void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (auto& p : cubeScreen)
		{
			//NDC
			auto point = p;
			point.x_ = ((point.x_ + 1) / 2) * 640;
			point.y_ = ((1 - point.y_) / 2) * 360;
			cout << point.x_ << " " << point.y_ << " " << point.z_ << endl;
		}
		glEnd();
		glFlush();
	}
}

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	zengine::matrix worldTransform;
	worldTransform.setTranslation(zengine::vector3(0, 0, 0));
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeWorld[i] = worldTransform.applyVector4(zengine::vector4(cubeModel[i], 1.0f));
	}

	
	zengine::matrix viewTransform;
	zengine::vector3 eye(0, 0, 0);
	zengine::vector3 focus(5, 5, 5);
	zengine::vector3 up(0, 1, 0);
	viewTransform.setLookAtLH(eye, focus, up);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeView[i] = viewTransform.applyVector4(cubeWorld[i]);
	}
	
	zengine::matrix projTransform;
	projTransform.setPerspectiveFovLH(zengine::angleToRadian(80), 640.0f / 360, 0.1f, 10.0f);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeProj[i] = projTransform.applyVector4(cubeView[i]);
	}

	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeScreen[i] = cubeProj[i];
		cubeScreen[i].homogeneous();
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

