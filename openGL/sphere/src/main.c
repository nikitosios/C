#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders.h"

float angle = 0.0f;
float pos = 0.0f;
char op = 0;

void timer (void)
{
	if (op)
		pos += 0.01f;
	else
		pos -= 0.01f;
	if (pos >= 2.0f)
		op = 0;
	if (pos <= -2.0f)
		op = 1;
	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;
	return;
}

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

	int resolution = 50;
	float radius = 0.5f;
	float x1, y1, z1, x2, y2, z2;
	float inc1, inc2, inc3, inc4, inc5, radius1, radius2;

	vec3_t * vertexes;
	vertexes = malloc(resolution * resolution * 6 * sizeof(vec3_t));

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

	vec3_t * colors;
	colors = malloc(resolution * resolution * 6 * sizeof(vec3_t));

	float r, g, b;

	srand(time(NULL));
	for (int i = 0; i < resolution * resolution * 6; ++i)
	{
		r = rand() % 1000 / 1000.0f;
		g = rand() % 1000 / 1000.0f;
		b = rand() % 1000 / 1000.0f;
		colors[i] = vec3(r, g, b);
	}

	GLuint vertexattributes;
	glGenVertexArrays(1, &vertexattributes);
	glBindVertexArray(vertexattributes);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,
			resolution * resolution * 6 * sizeof(vec3_t), vertexes,
			GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER,
			resolution * resolution * 6 * sizeof(vec3_t), colors,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			3 * sizeof(float), (void*)0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	double time, lastTime;
	mat4_t projection, view, model, MVP;
	mat4_t rotation, translation, scaling;

	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		time = glfwGetTime();
		if (time - lastTime >= 0.05)
		{
			timer();
			lastTime = time;
		}

		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programD);

		unsigned int MVPpos;
		MVPpos = glGetUniformLocation(programD, "MVP");

		projection = m4_perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
		view = m4_look_at(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		MVP = m4_perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
		MVP = m4_mul(MVP, m4_look_at(vec3(0.0f, 0.0f, 3.0f),
					vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
		scaling = m4_scaling(vec3(1.0f, 1.0f, 1.0f));
		rotation = m4_rotation(angle, vec3(0.0, 0.0, 1.0));
		translation = m4_translation(vec3(pos, 0.0, 0.0));
		model = m4_mul(translation, m4_mul(rotation, scaling));
		MVP = m4_mul(MVP, model);
		
		glBindVertexArray(vertexattributes);
		glUniformMatrix4fv(MVPpos, 1, GL_FALSE, (float *) &MVP);
		glDrawArrays(GL_TRIANGLES, 0, resolution * resolution * 6 * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
