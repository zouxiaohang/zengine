#include<iostream>

#include "src\math\vector.hpp"
#include "src\math\matrix.hpp"
#include "src\math\math_util.hpp"
#include "src\core\window.hpp"
#include "src\file\file.hpp"
#include "src\core\model.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

//#include <DirectXMath.h>
using namespace std;

namespace
{
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
}

zengine::modelPtr model;

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	zengine::window window(argc, argv, "zengine sample", 640.0f, 360.0f, -1.0f, 1.0f);

	zengine::file file("resource/triangle.zimage");
	model = file.getModel();

	// object space to world space
	zengine::matrix scale;
	zengine::matrix rotation;
	zengine::matrix translation;
	zengine::matrix worldTransform;
	scale.setScale(zengine::vector3(1, 1, 1));
	translation.setTranslation(zengine::vector3(0, -5, 0));
	rotation.setRotationZ(45);
	worldTransform = scale * rotation * translation;

	//wolrd space to eye space
	zengine::matrix viewTransform;
	zengine::vector3 eye(0, 0, -10);
	zengine::vector3 focus(0, 0, 0);
	zengine::vector3 up(0, 1, 0);
	viewTransform.setLookAtLH(eye, focus, up);

	//eye space to projection space
	zengine::matrix projTransform;
	projTransform.setPerspectiveFovLH(zengine::angleToRadian(90), 640.0f / 360, 0.1f, 1.0f);

	model->transform(worldTransform, zengine::model::WORLD_TRANSFORM);
	model->transform(viewTransform, zengine::model::VIEW_TRANDFORM);
	model->transform(projTransform, zengine::model::PROJECTION_TRANSFORM);
	//auto mvp = worldTransform * viewTransform * projTransform;
	//model->transform(mvp, zengine::model::WORLD_VIEW_PROJECT_TRANSFORM);
	model->transformToScreen(window.width(), window.height());

	auto display = []{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		const auto& screen = model->modelInScreen();
		for (int i = 0; i != screen.size() - 1; ++i)
		{
			drawLine(screen[i], screen[i + 1]);
		}
		drawLine(screen[screen.size() - 1], screen[0]);
		glFlush();
	};

	window.run(display);

	system("pause");
	return 0;
}

