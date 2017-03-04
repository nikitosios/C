#include <GL/glew.h>
#include <GL/gl.h>

static const GLfloat data[] = {
	-1.0, -1.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, -1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0
};

void prepareTriangleBuffers (GLuint * vboP, GLuint * vaoP)
{
	glGenVertexArrays(1, vaoP);
	glBindVertexArray(*vaoP);

	glGenBuffers(1, vboP);
	glBindBuffer(GL_ARRAY_BUFFER, *vboP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	return;
}

void prepareTriangle (unsigned int programD)
{
	GLint positionLocation, colorLocation;
	GLint vertexSize = 6 * sizeof(float);
	const void * vertexPositionOffset = 0;
	const void * vertexColorOffset =
		(const void *) (3 * sizeof(float));
	positionLocation = glGetAttribLocation(programD, "position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT,
				GL_FALSE, vertexSize,
				(const GLvoid*)vertexPositionOffset);
		glEnableVertexAttribArray(positionLocation);
	}

	colorLocation = glGetAttribLocation(programD, "color");
	if (colorLocation != -1)
	{
		glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE,
				vertexSize, (const GLvoid*)vertexColorOffset);
		glEnableVertexAttribArray(colorLocation);
	}

	return;
}
