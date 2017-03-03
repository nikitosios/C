#include <GL/glew.h>
#include <GL/gl.h>
#include "myvectors.h"

static const GLfloat data[] = {
	-1.0, -1.0, 0.0,
	1.0, -1.0, 0.0,
	0.0, 1.0, 0.0
};

void prepareTriangleBuffers (unsigned int * vboP, unsigned int * vaoP)
{
	glGenVertexArrays(1, vaoP);
	glBindVertexArray(*vaoP);

	glGenBuffers(1, vboP);
	glBindBuffer(GL_ARRAY_BUFFER, *vboP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	return;
}
