#include <GL/freeglut.h>
#include "api.h"

#define WINDOW_TITLE "My cube"

float rotate_x = 0, rotate_y = 0;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(10, 0.1, 0.0, 0.0);
	drawBox(100.0, 0.1, 100.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.5, 0.0);

	glTranslatef(0.0, 0.05, 0.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	drawCube(0.1, 1.0, 0.0, 0.0);

	glFlush();
	glutSwapBuffers();
	return;
}

void specialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		rotate_x += 5;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;
	else if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	glutPostRedisplay();
	return;
}

void init(void)
{
	float light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	float light_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 1.0, 1.0);
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
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
