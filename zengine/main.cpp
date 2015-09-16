#include<iostream>
#include <string>

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

const float windowWidth = 640.0f;
const float windowHeight = 360.0f;
const zengine::vector3 windowMid = zengine::vector3(windowWidth / 2, windowHeight / 2, 0.0f);

zengine::modelPtr model;

namespace
{
	const zengine::vector4 red(1.0f, 0.0f, 0.0f, 1.0f);
	const zengine::vector4 green(0.0f, 1.0f, 0.0f, 1.0f);
	const zengine::vector4 blue(0.0f, 0.0f, 1.0f, 1.0f);
	const zengine::vector4 yellow(1.0f, 1.0f, 0.0f, 1.0f);

	auto drawLine = [](const zengine::vector3& p1, 
						const zengine::vector3& p2, 
						const zengine::vector4& color){
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		glColor3f(color.x_, color.y_, color.z_);
		glVertex3f(p1.x_, p1.y_, p1.z_);
		glVertex3f(p2.x_, p2.y_, p2.z_);
		glEnd();
	};
	auto drawAxis = []{
		drawLine(windowMid, zengine::vector3(windowWidth, windowMid.y_, 0.0f), red);
		drawLine(windowMid, zengine::vector3(windowMid.x_, windowHeight, 0.0f), green);
		auto v4 = zengine::vector4((windowWidth - windowHeight) / 2,  0, 0.0f, 1.0f);
		drawLine(windowMid, zengine::vector3(v4.x_, v4.y_, v4.z_), blue);
	};
}

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	zengine::window window(argc, argv, "zengine sample", windowWidth, windowHeight, -1.0f, 1.0f);

	zengine::file file("resource/cube.zimage");
	model = file.getModel();

	// object space to world space
	zengine::matrix scale;
	zengine::matrix rotationY, rotationX;
	zengine::matrix translation;
	zengine::matrix worldTransform;
	scale.setScale(zengine::vector3(1, 1, 1));
	translation.setTranslation(zengine::vector3(0, -2, 1));
	rotationY.setRotationY(-60);
	rotationX.setRotationX(15);
	worldTransform = scale * rotationY * rotationX * translation;

	//wolrd space to eye space
	zengine::matrix viewTransform;
	zengine::vector3 eye(0, 0, -10);
	zengine::vector3 focus(0, 0, 0);
	zengine::vector3 up(0, 1, 0);
	viewTransform.setLookAtLH(eye, focus, up);

	//eye space to projection space
	zengine::matrix projTransform;
	projTransform.setPerspectiveFovLH(zengine::angleToRadian(90), window.width() / window.height(), 0.1f, 1000.0f);

	model->transform(worldTransform, zengine::model::WORLD_TRANSFORM);
	model->transform(viewTransform, zengine::model::VIEW_TRANDFORM);
	model->transform(projTransform, zengine::model::PROJECTION_TRANSFORM);
	//auto mvp = worldTransform * viewTransform * projTransform;
	//model->transform(mvp, zengine::model::WORLD_VIEW_PROJECT_TRANSFORM);
	model->transformToNDC();
	model->transformToScreen(window.width(), window.height());

	auto displayCube = []{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		drawAxis();
		const auto& screen = model->modelInScreen();
		const std::pair<int, int> indices[] = {
			{ 0, 3 }, { 0, 1 }, { 0, 4 }, { 1, 2 },
			{ 1, 5 }, { 2, 3 }, { 2, 6 }, { 3,7 },
			{ 4, 5 }, { 4, 7 }, { 5, 6 }, { 6, 7 },
		};
		for (const auto&pair : indices)
		{
			drawLine(screen[pair.first], screen[pair.second], yellow);
		}
		glFlush();
	};

	window.run(displayCube);

	system("pause");
	return 0;
}

