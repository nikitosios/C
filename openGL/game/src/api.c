void drawBox(float x, float y, float z, float a, float b, float c)
{
	unsigned short xr = x + a, yd = y + b, zf = z + c;

	glBegin(GL_POLYGON);
	glVertex3f(xr, y, z);
	glVertex3f(xr, yd, z);
	glVertex3f(x, yd, z);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xr, y, zf);
	glVertex3f(xr, yd, zf);
	glVertex3f(x, yd, zf);
	glVertex3f(x, y, zf);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xr, y, z);
	glVertex3f(xr, yd, z);
	glVertex3f(xr, yd, zf);
	glVertex3f(xr, y, zf);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y, zf);
	glVertex3f(x, yd, zf);
	glVertex3f(x, yd, z);
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xr, yd, zf);
	glVertex3f(xr, yd, z);
	glVertex3f(x, yd, z);
	glVertex3f(x, yd, zf);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(xr, y, z);
	glVertex3f(xr, y, zf);
	glVertex3f(x, y, zf);
	glVertex3f(x, y, z);
	glEnd();

	return;
}
