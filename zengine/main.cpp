#include<iostream>

#include "src\math\vector.hpp"
#include "src\math\matrix.hpp"
#include "src\math\math_util.hpp"
#include "src\core\window.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

//#include <DirectXMath.h>

using namespace std;

const int MODELSIZE = 3;
zengine::vector3 model[MODELSIZE] = {
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

zengine::vector4 modelWorld[MODELSIZE];
zengine::vector4 modelView[MODELSIZE];
zengine::vector4 modelProj[MODELSIZE];
zengine::vector4 modelNDC[MODELSIZE];
zengine::vector3 modelScreen[MODELSIZE];

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
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(p1.x_, p1.y_, p1.z_);
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
			drawLine(modelScreen[i], modelScreen[i + 1]);
		}
		drawLine(modelScreen[MODELSIZE - 1], modelScreen[0]);
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
		modelWorld[i] = worldTransform.applyVector4(zengine::vector4(model[i], 1.0f));
	}

	//wolrd space to eye space
	zengine::matrix viewTransform;
	zengine::vector3 eye(0, 0, -10);
	zengine::vector3 focus(0, 0, 0);
	zengine::vector3 up(0, 1, 0);
	viewTransform.setLookAtLH(eye, focus, up);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		modelView[i] = viewTransform.applyVector4(modelWorld[i]);
	}
	
	//eye space to projection space
	zengine::matrix projTransform;
	projTransform.setPerspectiveFovLH(zengine::angleToRadian(90), 640.0f / 360, 0.1f, 1.0f);
	for (int i = 0; i != MODELSIZE; ++i)
	{
		modelProj[i] = projTransform.applyVector4(modelView[i]);
	}

	//to NDC
	for (int i = 0; i != MODELSIZE; ++i)
	{
		modelNDC[i] = modelProj[i];
		modelNDC[i].homogeneous();
	}

	//to screen space
	for (int i = 0; i != MODELSIZE; ++i)
	{
		const auto& point = modelNDC[i];
		modelScreen[i].x_ = ((point.x_ + 1) / 2) * 640;
		modelScreen[i].y_ = ((1 - point.y_) / 2) * 360;
		//point.x_ = point.x_ * 640 + 640 / 2;
		//point.y_ = -point.y_ * 360 + 360 / 2;
	}

	zengine::window window(argc, argv, "zengine sample", 640.0f, 360.0f, -1.0f, 1.0f);
	window.run(display);

	system("pause");
	return 0;
}

