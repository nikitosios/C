void drawCube(float x, float y, float z, float a)
{
	glBegin(GL_POLYGON);
	glVertex3f(x, y - a, z - a);
	glVertex3f(x, y, z - a);
	glVertex3f(x - a, y, z - a);
	glVertex3f(x - a, y - a, z - a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y - a, z);
	glVertex3f(x, y, z);
	glVertex3f(x - a, y, z);
	glVertex3f(x - a, y - a, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y - a, z - a);
	glVertex3f(x, y, z - a);
	glVertex3f(x, y, z);
	glVertex3f(x, y - a, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - a, y - a, z);
	glVertex3f(x - a, y, z);
	glVertex3f(x - a, y, z -  a);
	glVertex3f(x - a, y - a, z - a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - a);
	glVertex3f(x - a, y, z - a);
	glVertex3f(x - a, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y - a, z - a);
	glVertex3f(x, y - a, z);
	glVertex3f(x - a, y - a, z);
	glVertex3f(x - a, y - a, z - a);
	glEnd();

	return;
}
