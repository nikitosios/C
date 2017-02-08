#include <GL/glut.h>
#include "api.h"

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

int *new_Vector(int x, int y, int z)
{
	int *vector = calloc(3, sizeof(int));
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	return vector;
}

int *multipleVectors(int *v1, int *v2)
{
	int *multipleVector;
	int mulx, muly, mulz;

	mulx = v2[2] * v1[1] - v1[2] * v2[1];
	muly = - (v2[2] * v1[0] - v1[2] * v2[0]);
	mulz = v2[1] * v1[0] - v1[1] * v2[0];
	multipleVector = new_Vector(mulx, muly, mulz);
	glNormalize(multipleVector);
	free(v1);
	free(v2);
	return multipleVector;
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

	glNormal3fv(multipleVectors(
				new_Vector(endx1 - startx1, 0, 0),
				new_Vector(startx2 - startx1,
					y2 - y1, startz2 - startz1)));
	glVertex3f(startx1, y1, startz1);
	glVertex3f(endx1, y1, startz1);
	glVertex3f(endx2, y2, startz2);
	glVertex3f(startx2, y2, startz2);

	glEnd();
	glBegin(GL_POLYGON);

	glNormal3fv(multiple_Vectors(
				new_Vector(endx1 - startx1, 0, 0),
				new_Vector(startx1 - startx2,
					y2 - y1, startz2 - startz1)
				));
	glVertex3f(startx1, y1, endz1);
	glVertex3f(endx1, y1, endz1);
	glVertex3f(endx2, y2, endz2);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	glNormal3fv(multipleVectors(
				new_Vector(0, 0, endz1 - startz1),
				new_Vector(startx2 - startx1, y2 - y1,
					endz2 - endz1)
				));
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
