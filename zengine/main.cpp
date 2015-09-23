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

const float windowWidth = 1024.0f;
const float windowHeight = 768.0f;
#include "src\file\bmp_loader.hpp"
int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

	zengine::window window(argc, argv, "zengine sample", windowWidth, windowHeight, -1.0f, 1.0f);
	  
	zengine::file file("resource/cube.zimage");
	zengine::bmpLoader loader("resource/zhuangbility.bmp");
	loader.load();

	auto model = file.getModel();
	model->addBmpTexture(loader.getBmp());

	window.addModel(model);

	window.run();


	

	system("pause");
	return 0;
}
