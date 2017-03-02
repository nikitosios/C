#include <GL/glew.h>
#include <GL/gl.h>
#include "myvectors.h"

static void initTriangleVertexes (Vertex *pvertex)
{
	/* vertex 0 */
	pvertex[0].x = -1.0;
	pvertex[0].y = -1.0;
	pvertex[0].z = 0.0;
	pvertex[0].nx = 0.0;
	pvertex[0].ny = 0.0;
	pvertex[0].nz = 1.0;
	pvertex[0].u = 0.0;
	pvertex[0].v = 0.0;

	/* vertex 1 */
	pvertex[1].x = 1.0;
	pvertex[1].y = -1.0;
	pvertex[1].z = 0.0;
	pvertex[1].nx = 0.0;
	pvertex[1].ny = 0.0;
	pvertex[1].nz = 1.0;
	pvertex[1].u = 1.0;
	pvertex[1].v = 0.0;

	/* vertex 2 */
	pvertex[2].x = 0.0;
	pvertex[2].y = 1.0;
	pvertex[2].z = 0.0;
	pvertex[2].nx = 0.0;
	pvertex[2].ny = 0.0;
	pvertex[2].nz = 1.0;
	pvertex[2].u = 0.0;
	pvertex[2].v = 1.0;

	return;
}

void prepareTriangleBuffers (unsigned int * vboP, unsigned int * vaoP)
{
	Vertex pvertex[3];
	initTriangleVertexes(pvertex);

	glGenBuffers(1, vboP);
	glBindBuffer(GL_ARRAY_BUFFER, *vboP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3,
			pvertex, GL_STATIC_DRAW);

	unsigned short pindices[3];
	pindices[0] = 0;
	pindices[1] = 1;
	pindices[2] = 2;

	glGenBuffers(1, vaoP);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *vaoP);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(unsigned short) * 3, pindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, *vboP);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)12);
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)24);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *vaoP);

	return;
}
