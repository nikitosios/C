#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders.h"

int main (void)
{
	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow * window = glfwCreateWindow(1024, 768, "Sphere", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vertShader, fragShader, programD;
	prepareShader(&vertShader, "shaders/vertex.vsh", GL_VERTEX_SHADER);
	prepareShader(&fragShader, "shaders/fragment.fsh", GL_FRAGMENT_SHADER);
	GLuint shaders[] = {vertShader, fragShader};
	prepareProgram(&programD, shaders, 2);

	int resolution = 100;
	float radius = 0.5f;
	float x1, y1, z1, x2, y2, z2;
	float inc1, inc2, inc3, inc4, inc5, radius1, radius2;

	vec3_t vertexes[resolution * resolution * 6];

	int i = 0;
	for (int w = 0; w < resolution; ++w)
	{
		for (int h = (- resolution / 2); h < (resolution / 2); ++h)
		{
			inc1 = w / (float) resolution * 2 * M_PI;
			inc2 = (w + 1) / (float) resolution * 2 * M_PI;
			inc3 = h / (float) resolution * 2 * M_PI;
			inc4 = (h + 1) / (float) resolution * 2 * M_PI;

			x1 = sinf(inc1);
			y1 = cosf(inc1);
			x2 = sinf(inc2);
			y2 = cosf(inc2);

			radius1 = radius * cosf(inc3);
			radius2 = radius * cosf(inc4);

			z1 = radius * sinf(inc3);
			z2 = radius * sinf(inc4);

			vertexes[i++] = vec3(radius1 * x1, z1, radius1 * y1);
			vertexes[i++] = vec3(radius1 * x2, z1, radius1 * y1);
			vertexes[i++] = vec3(radius2 * x2, z2, radius2 * y2);
			vertexes[i++] = vec3(radius1 * x1, z1, radius1 * y1);
			vertexes[i++] = vec3(radius2 * x2, z2, radius2 * y2);
			vertexes[i++] = vec3(radius2 * x1, z2, radius2 * y1);
		}
	}

	GLuint vertexattributes;
	glGenVertexArrays(1, &vertexattributes);
	glBindVertexArray(vertexattributes);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertexes, vertexes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			3 * sizeof(float), (void*)0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programD);

		glDrawArrays(GL_TRIANGLES, 0, resolution * resolution * 6 * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
