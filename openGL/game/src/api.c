#include <math.h>
#include "api.h"

void drawSquare(float a, float b)
{
	float startx = 0 - a / 2, starty = b / 2;
	float endx = a / 2, endy = 0 - b / 2;

	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(startx, starty, 0);
	glVertex3f(endx, starty, 0);
	glVertex3f(endx, endy, 0);
	glVertex3f(startx, endy, 0);

	glEnd();
}

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

float *new_Vector(float x, float y, float z)
{
	float *vector = calloc(3, sizeof(float));
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	return vector;
}

float *multipleVectors(float *v1, float *v2)
{
	float *multipleVector;
	float mulx, muly, mulz;

	mulx = v2[2] * v1[1] - v1[2] * v2[1];
	muly = - (v2[2] * v1[0] - v1[2] * v2[0]);
	mulz = v2[1] * v1[0] - v1[1] * v2[0];
	multipleVector = new_Vector(mulx, muly, mulz);
	free(v1);
	free(v2);
	return multipleVector;
}

void drawPyramid(float a, float h)
{
	float x = 0.0, y = h / 2, z = 0;
	float startx = 0 - a / 2, yd = 0 - h / 2, startz = a / 2;
	float endx = a / 2, endz = 0 - a / 2;

	glBegin(GL_QUADS);

	/* down */
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(startx, yd, startz);
	glVertex3f(endx, yd, startz);
	glVertex3f(endx, yd, endz);
	glVertex3f(startx, yd, endz);

	glEnd();
	glBegin(GL_TRIANGLES);

	/* front */
	glNormal3fv(multipleVectors(
				new_Vector(endx - startx, 0, 0),
				new_Vector(x - startx, y - yd, endz - startz)));
	glTexCoord2f(0.0, 0.0);
	glVertex3f(startx, yd, startz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(endx, yd, startz);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(x, y, z);

	/* back */
	glNormal3fv(multipleVectors(
				new_Vector(startx - endx, 0, 0),
				new_Vector(x - endx, y - yd, z - endz)));
	glTexCoord2f(0.0, 0.0);
	glVertex3f(endx, yd, endz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(startx, yd, endz);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(x, y, z);

	/* left */
	glNormal3fv(multipleVectors(
				new_Vector(0, 0, startz - endz),
				new_Vector(x - startx, y - yd, z - endz)));
	glTexCoord2f(0.0, 0.0);
	glVertex3f(startx, yd, endz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(startx, yd, startz);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(x, y, z);

	/* right */
	glNormal3fv(multipleVectors(
				new_Vector(0, 0, endz - startz),
				new_Vector(x - endx, y - yd, z - startz)));
	glTexCoord2f(0.0, 0.0);
	glVertex3f(endx, yd, startz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(endx, yd, endz);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(x, y, z);

	glEnd();

	return;
}

void drawPyramidDown(float a, float b, float h)
{
	float startx1 = 0 - a / 2, y1 = h / 2, startz1 = a / 2;
	float endx1 = a / 2, endz1 = 0 - a / 2;
	float startx2 = 0 - b / 2, y2 = 0 - h / 2, startz2 = b / 2;
	float endx2 = b / 2, endz2 = 0 - b / 2;

	glBegin(GL_QUADS);

	/* up */
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(startx1, y1, startz1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(endx1, y1, startz1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(endx1, y1, endz1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(startx1, y1, endz1);

	/* down */
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(startx2, y2, startz2);
	glVertex3f(endx2, y2, startz2);
	glVertex3f(endx2, y2, endz2);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* front */
	glNormal3fv(multipleVectors(
				new_Vector(startx1 - endx1, 0, 0),
				new_Vector(endx2 - endx1,
					y2 - y1, startz2 - startz1)));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(startx1, y1, startz1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(endx1, y1, startz1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(endx2, y2, startz2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(startx2, y2, startz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* back */
	glNormal3fv(multipleVectors(
				new_Vector(endx1 - startx1, 0, 0),
				new_Vector(startx2 - startx1,
					y2 - y1, startz2 - startz1)));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(startx1, y1, endz1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(endx1, y1, endz1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(endx2, y2, endz2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* left */
	glNormal3fv(multipleVectors(
				new_Vector(0, 0, endz1 - startz1),
				new_Vector(startx2 - startx1, y2 - y1,
					startz2 - startz1)));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(startx1, y1, endz1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(startx1, y1, startz1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(startx2, y2, startz2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(startx2, y2, endz2);

	glEnd();
	glBegin(GL_POLYGON);

	/* right */
	glNormal3fv(multipleVectors(
				new_Vector(0, 0, startz1 - endz1),
				new_Vector(endx2 - endx1, y2 - y1,
					endz2 - endz1)));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(endx1, y1, startz1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(endx1, y1, endz1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(endx2, y2, endz2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(endx2, y2, startz2);

	glEnd();
	return;
}

void drawEye(float radius, unsigned int tex)
{
	GLUquadricObj* quadObj; 

	glRotatef(180, 0.0, 0.0, -1.0);
	glRotatef(-25, 1.0, 0.0, 0.0);
	glScalef(1.5, 1.1, 1.0);

	quadObj = gluNewQuadric(); 
	gluQuadricTexture(quadObj, GL_TRUE);
	gluQuadricNormals(quadObj, GLU_SMOOTH);

	glBindTexture(GL_TEXTURE_2D, tex);
	gluSphere(quadObj, radius, 32, 32); 
	gluDeleteQuadric(quadObj);

	return;
}

void drawMLGPyramid (void)
{
	glTranslatef(3.0, 1.1, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	glBindTexture(GL_TEXTURE_2D, pyramidT);
	glEnable(GL_TEXTURE_2D);
	drawPyramidDown(1.0, 2.0, 2.0);
	glTranslatef(0.0, 1.6, 0.0);
	drawPyramid(1.0, 1.1);
	glTranslatef(0.0, 0.0, 0.18);
	glBindTexture(GL_TEXTURE_2D, eyeT);
	glEnable(GL_TEXTURE_2D);
	drawEye(0.08, eyeT);
	glTranslatef(0.22, 0.0, 0.0);
	glTranslatef(0.0, -1.6, 0.0);
	glDisable(GL_TEXTURE_2D);
	glRotatef(-angle, 0.0, 1.0, 0.0);
	glTranslatef(-3.0, -1.1, 0.0);

	return;
}
