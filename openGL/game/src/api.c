#include <GL/glut.h>

void drawBox(float a, float b, float c)
{
	float startx = 0 - a / 2, starty = b / 2, startz = c / 2;
	float endx = a / 2, endy = 0 - b / 2, endz = 0 - c / 2;

	glBegin(GL_QUADS);
	
	/* front */
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(startx, starty, startz);
	glVertex3f(endx, starty, startz);
	glVertex3f(endx, endy, startz);
	glVertex3f(startx, endy, startz);
	
	/* back */
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(startx, starty, endz);
	glVertex3f(endx, starty, endz);
	glVertex3f(endx, endy, endz);
	glVertex3f(startx, endy, endz);
	
	/* left */
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(startx, starty, startz);
	glVertex3f(startx, starty, endz);
	glVertex3f(startx, endy, endz);
	glVertex3f(startx, endy, startz);
	
	/* right */
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(endx, starty, startz);
	glVertex3f(endx, starty, endz);
	glVertex3f(endx, endy, endz);
	glVertex3f(endx, endy, startz);
	
	/* up */
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(startx, starty, endz);
	glVertex3f(endx, starty, endz);
	glVertex3f(endx, starty, startz);
	glVertex3f(startx, starty, startz);
	
	/* down */
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(startx, endy, endz);
	glVertex3f(endx, endy, endz);
	glVertex3f(endx, endy, startz);
	glVertex3f(startx, endy, startz);
	
	glEnd();
}

void drawPyramidDown(float a, float b, float h)
{
	return;
}
