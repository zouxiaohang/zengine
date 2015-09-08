#include<iostream>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

using namespace std;

namespace
{
	void init(void)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	}
	void drawString(const char* str)
	{
		static int isFirstCall = 1;
		static GLuint lists;
		if (isFirstCall) {
			isFirstCall = 0;
			lists = glGenLists(128);
			wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
		}
		for (; *str != '\0'; ++str)
			glCallList(lists + *str);
	}
	void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2f(0.4f, 0.5f);
		glScalef(1, 5, 1);
		drawString("hello zengine");
		glutSwapBuffers();
		glFlush();
	}
}

int main(int argc, char** argv)
{
	cout << "hello zengine" << endl;

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

