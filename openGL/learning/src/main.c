#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"
#undef MATH_3D_IMPLEMENTATION
#include "constants.h"
#include "shaders.h"
#include "render.h"

mat4_t projectionMatrix, viewMatrix, modelMatrix, MVP;
mat4_t translationMatrix, rotationMatrix, scalingMatrix;
GLuint programD;
GLFWwindow * window;

int main (void)
{
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

	while (!glfwWindowShouldClose(window))
	{
		render();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
