#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"
#include "constants.h"
#include "utils.h"

mat4_t projectionMatrix, viewMatrix, modelMatrix, MVP;
mat4_t translationMatrix, rotationMatrix, scalingMatrix;
GLuint programD;
float angle;
GLFWwindow * window;
double lastTime, time;

int main (void)
{
	angle = 0.0f;

	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE, NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vertShader;
	prepareShader(&vertShader, VERTEX_SHADER_NAME, GL_VERTEX_SHADER);

	GLuint fragShader;
	prepareShader(&fragShader, FRAGMENT_SHADER_NAME, GL_FRAGMENT_SHADER);

	GLuint shaders[] = {vertShader, fragShader};
	prepareProgram(&programD, shaders, 2);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		time = glfwGetTime();
		if (time - lastTime >= DELTA_TIME)
			timer();

		render();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
