#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct Vertex
{
	float x, y, z; /* vertex */
	float nx, ny, nz; /* normal */
	float s0, t0; /* texcoord */
} Vertex;

unsigned int vbo, vao;

void initTriangleVertexes (Vertex* pvertex)
{
	/* vertex 0 */
	pvertex[0].x = -1.0;
	pvertex[0].y = -1.0;
	pvertex[0].z = 0.0;
	pvertex[0].nx = 0.0;
	pvertex[0].ny = 0.0;
	pvertex[0].nz = 1.0;
	pvertex[0].s0 = 0.0;
	pvertex[0].t0 = 0.0;

	/* vertex 1 */
	pvertex[1].x = 1.0;
	pvertex[1].y = -1.0;
	pvertex[1].z = 0.0;
	pvertex[1].nx = 0.0;
	pvertex[1].ny = 0.0;
	pvertex[1].nz = 1.0;
	pvertex[1].s0 = 1.0;
	pvertex[1].t0 = 0.0;

	/* vertex 2 */
	pvertex[2].x = 0.0;
	pvertex[2].y = 1.0;
	pvertex[2].z = 0.0;
	pvertex[2].nx = 0.0;
	pvertex[2].ny = 0.0;
	pvertex[2].nz = 1.0;
	pvertex[2].s0 = 0.0;
	pvertex[2].t0 = 1.0;

	return;
}

int main (void)
{
	/* initialize openGL */
	glfwInit();
	glfwDefaultWindowHints();
	GLFWwindow* window = glfwCreateWindow(300, 300, "glBegin/End for dweebs", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	/* initialize triangle vertexes */
	Vertex pvertex[3];
	initTriangleVertexes(pvertex);

	/* load vertex buffer to video memory */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, pvertex, GL_STATIC_DRAW);

	unsigned short pindices[3];
	pindices[0] = 0;
	pindices[1] = 1;
	pindices[2] = 2;

	/*   */
	glGenBuffers(1, &vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, pindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)12);
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)24);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao);

	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		/* set the triangle color to red */
		glColor3f(1.0, 0.0, 0.0);
		/* draw triangle */
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);

		/* i don't know what to write here */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* destroy window and terminate openGL activity */
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
