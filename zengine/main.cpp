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

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	zengine::window window(argc, argv, "zengine sample", windowWidth, windowHeight, -1.0f, 1.0f);

	zengine::file file("resource/cube.zimage");
	//model = file.getModel();
	window.addModel(file.getModel());

	window.run();

	system("pause");
	return 0;
}
