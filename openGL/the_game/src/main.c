#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "constants.h"
#include "my_opengl_api.h"

const static GLfloat sky_vertex_data[] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f
};

const static GLfloat sky_uv_data[] = {
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f
};

static const GLfloat land_vertex_data[] = {
	-100.0f, 0.0f, 100.0f,
	100.0f, 0.0f, 100.0f,
	100.0f, 0.0f, -100.0f,
	100.0f, 0.0f, -100.0f,
	-100.0f, 0.0f, -100.0f,
	-100.0f, 0.0f, 100.0f
};

static const GLfloat land_uv_data[] = {
	0.0f, 1.0f - 0.0f,
	100.0f, 1.0f - 0.0f,
	100.0f, 1.0f - 100.0f,
	100.0f, 1.0f - 100.0f,
	0.0f, 1.0f - 100.0f,
	0.0f, 1.0f - 0.0f
};

GLFWwindow * window;

int main (void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
		return -1;
	}

	GLuint shader[2], programD;
	prepareShader(shader, "shaders/vertex.vsh", GL_VERTEX_SHADER);
	prepareShader(shader + 1, "shaders/fragment.fsh", GL_FRAGMENT_SHADER);
	prepareProgram(&programD, shader, 2);

	object_data * skybox = malloc(sizeof(object_data));
	make_object(skybox, sizeof sky_vertex_data, sky_vertex_data, sky_uv_data, "skybox.jpg", programD);

	object_data * land = malloc(sizeof(object_data));
	make_object(land, sizeof land_vertex_data, land_vertex_data, land_uv_data, "land.jpg", programD);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	double time, lastTime;
	lastTime = time = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox->projectionMatrix = m4_perspective(45.0f, (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		skybox->viewMatrix = m4_look_at(vec3(0.0f, 4.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		skybox->scalingMatrix = m4_scaling(vec3(100.0f, 100.0f, 100.0f));
		skybox->rotatingMatrix = m4_identity();
		skybox->translatingMatrix = m4_identity();
		drawObject(skybox);

		land->projectionMatrix = skybox->projectionMatrix;
		land->viewMatrix = skybox->viewMatrix;
		land->scalingMatrix = m4_identity();
		land->rotatingMatrix = m4_identity();
		land->translatingMatrix = m4_translation(vec3(0.0f, 0.0f, 0.0f));
		drawObject(land);

		if ((time = glfwGetTime()) - lastTime >= TIME_STEP)
		{
			/* code */
			lastTime = time;
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
