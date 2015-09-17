#include "window.hpp"
#include "color.hpp"
#include "../math/matrix.hpp"
#include "../math/math_util.hpp"
#include "../math/vector.hpp"
#include "../math/line.hpp"

std::unique_ptr<zengine::window> WINDOW;

namespace
{
	zengine::vector3 position(0, 0, 0);
	zengine::vector3 rotation(0, 0, 0);

	void handleSpecialKeyBoard(int key, int x, int y)
	{
		if (key == GLUT_KEY_UP)
			position.y_ -= 0.5;
		if (key == GLUT_KEY_DOWN)
			position.y_ += 0.5;
		
		if (key == GLUT_KEY_LEFT)
			position.x_ -= 0.5;
		if (key == GLUT_KEY_RIGHT)
			position.x_ += 0.5;
	}

	void handleNormalKeyBoard(unsigned char key, int x, int y)
	{
		if (key == 'w')
			rotation.x_ += 5;
		if (key == 's')
			rotation.x_ -= 5;

		if (key == 'a')
			rotation.y_ += 5;
		if (key == 'd')
			rotation.y_ -= 5;

		if (key == 27) // esc pressed
			exit(0);
	}
}

namespace
{
	zengine::modelPtr MODEL;

	auto drawPixel = [](const zengine::vector3& p, const zengine::vector4& color)
	{
		glBegin(GL_POINTS);
		glColor3f(color.x_, color.y_, color.z_);
		glVertex3f(p.x_, p.y_, p.z_);
		glEnd();
	};
	auto drawLine = [](const zengine::vector3& p1,
						const zengine::vector3& p2,
						const zengine::vector4& color){
		//glLineWidth(1.0f);
		//glBegin(GL_LINES);
		//glColor3f(color.x_, color.y_, color.z_);
		//glVertex3f(p1.x_, p1.y_, p1.z_);
		//glVertex3f(p2.x_, p2.y_, p2.z_);
		//glEnd();
		auto start = p1, end = p2;
		auto xrange = std::fabs(end.x_ - start.x_);
		auto yrange = std::fabs(end.y_ - start.y_);
		auto k = (end.y_ - start.y_) / (end.x_ - start.x_);
		auto b = end.y_ - k * end.x_;
		if (xrange > yrange)
		{
			if (start.x_ > end.x_)
			std::swap(start, end);
			for (auto x = start.x_; x <= end.x_; ++x)
			{
				auto y = k * x + b;
				drawPixel(zengine::vector3(x, y, 1.0f), zengine::white);
			}
		}
		else
		{
			if (start.y_ > end.y_)
				std::swap(start, end);
			for (auto y = start.y_; y <= end.y_; ++y)
			{
				auto x = (y - b) / k;
				drawPixel(zengine::vector3(x, y, 1.0f), zengine::white);
			}
		}
	};
	float zinterpolate(float z1, float z2, float t)
	{
		return z1 * (1 - t) + z2 * t;
	}
	auto displayCube = []{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		MODEL->clear();
		WINDOW->update();
		const auto& screen = MODEL->modelInScreen();
		const std::pair<int, int> indicesPairs[] = {
			{ 0, 3 }, { 0, 1 }, { 0, 4 }, { 1, 2 },
			{ 1, 5 }, { 2, 3 }, { 2, 6 }, { 3, 7 },
			{ 4, 5 }, { 4, 7 }, { 5, 6 }, { 6, 7 },
		};
		//// fill zbuffer
		//for (const auto& pair : indicesPairs)
		//{
		//	const auto& start = screen[pair.first], end = screen[pair.second];
		//	//zengine::line line(screen[pair.first], screen[pair.second] - screen[pair.first]);
		//	auto length = (end - start).length();
		//	auto k = (end.y_ - start.y_) / (end.x_ - start.x_);
		//	auto b = end.y_ - k * end.x_;
		//	for (auto x = start.x_; x <= end.x_; ++x)
		//	{
		//		auto y = k * x + b;
		//		auto len = sqrtf((y - start.y_) * (y - start.y_) + (x - start.x_) * (x - start.x_));
		//		auto t = len / length;
		//		auto z = zinterpolate(start.z_, end.z_, t);
		//		WINDOW->setZbuffer(x, y, z);
		//	}
		//}

		for (const auto& pair : indicesPairs)
		{
			drawLine(screen[pair.first], screen[pair.second], zengine::white);
		}
		glFlush();
	};
}

namespace zengine
{
	window::window(int argc, char** argv, const char * title, float width, float height, float fnear, float ffar) :
		width_(width), height_(height), near_(fnear), far_(ffar), title_(title)
	{
		init(argc, argv);
		clearZbuffer();
	}

	window::~window()
	{
		auto w = int(width_);
		for (auto i = 0; i != w; ++i)
		{
			delete[] zbuffer_[i];
		}
		delete[] zbuffer_;
	}

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

		glutSpecialFunc(handleSpecialKeyBoard);
		glutKeyboardFunc(handleNormalKeyBoard);
	}

	void window::run()
	{
		MODEL = model_;
		WINDOW = std::make_unique<window>(*this);
		//update();

		glutDisplayFunc(displayCube);
		while (true)
		{
			//glutPostRedisplay();
			glutIdleFunc(displayCube);
			glutMainLoop();
		}
	}

	void window::update()
	{
		// object space to world space
		zengine::matrix scale;
		zengine::matrix rotationY, rotationX;
		zengine::matrix translation;
		zengine::matrix worldTransform;
		scale.setScale(zengine::vector3(1, 1, 1));
		translation.setTranslation(zengine::vector3(0, -2, 1) + position);
		rotationX.setRotationX(15 + rotation.x_);
		rotationY.setRotationY(-60 + rotation.y_);
		worldTransform = scale * rotationY * rotationX * translation;

		//wolrd space to camera space
		zengine::matrix viewTransform;
		zengine::vector3 eye(0, 0, -10);
		zengine::vector3 focus(0, 0, 0);
		zengine::vector3 up(0, 1, 0);
		viewTransform.setLookAtLH(eye, focus, up);

		//eye space to clip space
		zengine::matrix projTransform;
		projTransform.setPerspectiveFovLH(zengine::angleToRadian(90), width() / height(), 0.1f, 1000.0f);

		model_->transform(worldTransform, zengine::model::WORLD_TRANSFORM);
		model_->transform(viewTransform, zengine::model::VIEW_TRANDFORM);
		model_->transform(projTransform, zengine::model::PROJECTION_TRANSFORM);
		//auto mvp = worldTransform * viewTransform * projTransform;
		//model_->transform(mvp, zengine::model::WORLD_VIEW_PROJECT_TRANSFORM);
		model_->transformToNDC();
		model_->transformToScreen(width(), height());

		//clearZbuffer();
	}

	void window::clearZbuffer()
	{
		auto h = int(height_);
		auto w = int(width_);
		zbuffer_ = new float*[w];
		for (auto i = 0; i != w; ++i)
		{
			zbuffer_[i] = new float[h];
			std::fill_n(zbuffer_[i], h, std::numeric_limits<float>::max());
		}
	}

	void window::setZbuffer(float w, float h, float v)
	{
		auto& z = zbuffer_[int(w)][int(h)];
		if (z > v)
			z = v;
	}
}