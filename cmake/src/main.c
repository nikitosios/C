#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "vars.h"

void display (void)
{
	GLUquadric* obj;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0,
			0, 0, 0,
			0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	obj = gluNewQuadric();
	gluSphere(obj, 1.0, 20, 20);
	gluDeleteQuadric(obj);

	glutSwapBuffers();
	return;
}

void initGL (void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)window_width / (double)window_height,
			1.0, 200.0);
	return;
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow(window_title);
	initGL();

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
