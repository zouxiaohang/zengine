#include<iostream>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include "src\math\vector.hpp"
#include "src\math\matrix.hpp"
#include "src\math\math_util.hpp"

//#include <DirectXMath.h>

using namespace std;

const int MODELSIZE = 3;
zengine::vector3 cubeModel[MODELSIZE] = {
	{0,0,0},
	{10, 0, 0},
	{0, 10, 0}
	//{ 10, 10, 10 },
	//{ -10, 10, 10 },
	//{ -10, 10, -10 },
	//{ 10, 10, -10 },
	//{ 10, -10, 10 },
	//{ -10, -10, 10 },
	//{ -10, -10, -10 },
	//{ 10, -10, -10 }
};

zengine::vector4 cubeWorld[MODELSIZE];
zengine::vector4 cubeView[MODELSIZE];
zengine::vector4 cubeProj[MODELSIZE];
zengine::vector4 cubeNDC[MODELSIZE];
zengine::vector3 cubeScreen[MODELSIZE];

namespace
{
	void init(void)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glLoadIdentity();
		glOrtho(0, 640, 0, 360, -1, 1);
	}
	void drawLine(const zengine::vector3& p1, const zengine::vector3& p2)
	{
		glLineWidth(2.0f);
		glBegin(GL_LINE_STRIP); // set the Mode
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(p1.x_, p1.y_, p1.z_);//
		glVertex3f(p2.x_, p2.y_, p2.z_);
		glEnd();
		//glFlush();

	}
	void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		for (int i = 0; i != MODELSIZE - 1; ++i)
		{
			drawLine(cubeScreen[i], cubeScreen[i + 1]);
		}
		drawLine(cubeScreen[MODELSIZE - 1], cubeScreen[0]);
		glFlush();
	}
}

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	// object space to world space
	zengine::matrix scale;
	zengine::matrix rotation;
	zengine::matrix translation;
	zengine::matrix worldTransform;

	scale.setScale(zengine::vector3(1, 1, 1));
	translation.setTranslation(zengine::vector3(0, -5, 0));
	rotation.setRotationZ(45);
	worldTransform = scale * rotation * translation;
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeWorld[i] = worldTransform.applyVector4(zengine::vector4(cubeModel[i], 1.0f));
	}

	//wolrd space to eye space
	zengine::matrix viewTransform;
	zengine::vector3 eye(0, 0, -10);
	zengine::vector3 focus(0, 0, 0);
	zengine::vector3 up(0, 1, 0);
	viewTransform.setLookAtLH(eye, focus, up);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeView[i] = viewTransform.applyVector4(cubeWorld[i]);
	}
	
	//eye space to projection space
	zengine::matrix projTransform;
	projTransform.setPerspectiveFovLH(zengine::angleToRadian(90), 640.0f / 360, 0.1f, 1.0f);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeProj[i] = projTransform.applyVector4(cubeView[i]);
	}

	//to NDC
	for (int i = 0; i != MODELSIZE; ++i)
	{
		cubeNDC[i] = cubeProj[i];
		cubeNDC[i].homogeneous();
	}

	//to screen space
	for (int i = 0; i != MODELSIZE; ++i)
	{
		const auto& point = cubeNDC[i];
		cubeScreen[i].x_ = ((point.x_ + 1) / 2) * 640;
		cubeScreen[i].y_ = ((1 - point.y_) / 2) * 360;
		//point.x_ = point.x_ * 640 + 640 / 2;
		//point.y_ = -point.y_ * 360 + 360 / 2;
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

