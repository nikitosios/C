#include <GL/freeglut.h>

void drawBox(float a, float b, float c, float R, float G, float B)
{
	float x = 0 + a / 2, y = 0 + b / 2, z = 0 + c / 2;
	float xr = x - a, yd = y - b, zf = z - c;

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(xr, y, z);
	glVertex3f(xr, yd, z);
	glVertex3f(x, yd, z);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(xr, y, zf);
	glVertex3f(xr, yd, zf);
	glVertex3f(x, yd, zf);
	glVertex3f(x, y, zf);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(xr, y, z);
	glVertex3f(xr, yd, z);
	glVertex3f(xr, yd, zf);
	glVertex3f(xr, y, zf);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(x, y, zf);
	glVertex3f(x, yd, zf);
	glVertex3f(x, yd, z);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(xr, yd, zf);
	glVertex3f(xr, yd, z);
	glVertex3f(x, yd, z);
	glVertex3f(x, yd, zf);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(xr, y, z);
	glVertex3f(xr, y, zf);
	glVertex3f(x, y, zf);
	glVertex3f(x, y, z);
	glEnd();

	return;
}
