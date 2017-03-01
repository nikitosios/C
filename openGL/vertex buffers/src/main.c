#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "shaders.h"

static const float vertexData[] = {-1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 0.0, 1.0, 0.0};

unsigned int vbo, vao;

void createBuffers (void)
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	return;
}

void deleteBuffers (void)
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	return;
}

void bindBuffers (void)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	return;
}

void unbindBuffers (void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}

int main (void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
		return -1;
	}

	glfwDefaultWindowHints();

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
			NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Failed to initialize GLEW.\n");
		return -1;
	}

	createBuffers();
	bindBuffers();
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		char error;
		GLuint programId = prepareProgram(&error);
		glUseProgram(programId);

		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	unbindBuffers();
	deleteBuffers();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
