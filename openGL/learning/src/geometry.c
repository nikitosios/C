#include <GL/glew.h>

static const GLfloat data[] = {
	-0.5, -0.5, 0.0,
	1.0, 0.0, 0.0,
	0.5, -0.5, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.5, 0.0,
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
