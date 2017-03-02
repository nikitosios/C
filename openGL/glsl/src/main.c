#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "myvectors.h"
#include "shaders.h"
#include "mygeometry.h"

int main (void)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	unsigned int vertShader;
	prepareShader(&vertShader, "shaders/vertex.vsh", GL_VERTEX_SHADER);

	unsigned int fragShader;
	prepareShader(&fragShader, "shaders/fragment.fsh", GL_FRAGMENT_SHADER);

	unsigned int shaders[] = {vertShader, fragShader};
	unsigned int programD;
	prepareProgram(&programD, shaders, 2);
	glUseProgram(programD);

	unsigned int vbo, vao;
	prepareTriangleBuffers(&vbo, &vao);

	while (!glfwWindowShouldClose(window))
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void *)0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
