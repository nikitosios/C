#include <GL/freeglut.h>
#include "api.h"

#define WINDOW_TITLE "My cube"

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-100.0, -100.0, 0.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(100.0, -100.0, 0.0);
	glEnd();

	drawCube(0.5, 0.5, 1.0, 1.0);

	glFlush();
	glutSwapBuffers();
	return;
}

void specialKeys(int key, int x, int y)
{
	glutPostRedisplay();
	return;
}

int main(int argc, char *argv[])
{
	unsigned short window_width = 640, window_height = 480;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(WINDOW_TITLE);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
