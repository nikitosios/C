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
	float startx1 = 0 - a / 2, y1 = h / 2, startz1 = a / 2;
	float endx1 = a / 2, endz1 = 0 - a / 2;
	float startx2 = 0 - b / 2, y2 = 0 - h / 2, startz2 = b / 2;
	float endx2 = b / 2, endz2 = 0 - b / 2;

	glBegin(GL_QUADS);

	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(startx1, y1, startz1);
	glVertex3f(endx1, y1, startz1);
	glVertex3f(endx1, y1, endz1);
	glVertex3f(startx1, y1, endz1);

	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(startx2, y2, startz2);
	glVertex3f(endx2, y2, startz2);
	glVertex3f(endx2, y2, endz2);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* glNormal3f(); */
	glVertex3f(startx1, y1, startz1);
	glVertex3f(endx1, y1, startz1);
	glVertex3f(endx2, y2, startz2);
	glVertex3f(startx2, y2, startz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* glNormal3f(); */
	glVertex3f(startx1, y1, endz1);
	glVertex3f(endx1, y1, endz1);
	glVertex3f(endx2, y2, endz2);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* glNormal3f(); */
	glVertex3f(startx1, y1, endz1);
	glVertex3f(startx1, y1, startz1);
	glVertex3f(startx2, y2, startz2);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* glNormal3f(); */
	glVertex3f(endx1, y1, startz1);
	glVertex3f(endx1, y1, endz1);
	glVertex3f(endx2, y2, endz2);
	glVertex3f(endx2, y2, startz2);

	glEnd();
	return;
}
