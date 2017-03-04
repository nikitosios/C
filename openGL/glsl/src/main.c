#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "shaders.h"
#include "geometry.h"

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
	prepareShader(&vertShader, VERTEX_SHADER_NAME, GL_VERTEX_SHADER);

	GLuint fragShader;
	prepareShader(&fragShader, FRAGMENT_SHADER_NAME, GL_FRAGMENT_SHADER);

	GLuint shaders[] = {vertShader, fragShader};
	GLuint programD;
	prepareProgram(&programD, shaders, 2);

	GLuint vbo, vao;
	prepareTriangleBuffers(&vbo, &vao);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		prepareTriangle(programD);
		glUseProgram(programD);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
