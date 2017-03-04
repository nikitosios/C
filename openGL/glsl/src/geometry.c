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
	GLint posLoc, colLoc;
	GLint vertexSize = 6 * sizeof(float);
	const void * vPosOffset = 0;
	const void * vColOffset =
		(const void *) (3 * sizeof(float));

	posLoc = glGetAttribLocation(programD, "position");
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE,
			vertexSize, (void *) vPosOffset);
	glEnableVertexAttribArray(posLoc);

	colLoc = glGetAttribLocation(programD, "color");
	glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE,
			vertexSize, (const GLvoid*)vColOffset);
	glEnableVertexAttribArray(colLoc);

	return;
}
