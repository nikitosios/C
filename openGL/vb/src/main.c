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

	GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE, NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vertShader;
	prepareShader(&vertShader, "shaders/vertex.vsh", GL_VERTEX_SHADER);

	GLuint fragShader;
	prepareShader(&fragShader, "shaders/fragment.fsh",
			GL_FRAGMENT_SHADER);

	GLuint shaders[] = {vertShader, fragShader};
	GLuint programD;
	prepareProgram(&programD, shaders, 2);

	GLuint vbo, vao;
	prepareTriangleBuffers(&vbo, &vao);

	while (!glfwWindowShouldClose(window))
	{
		glUseProgram(programD);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
