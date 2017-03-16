#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "constants.h"
#include "my_opengl_api.h"

static const GLfloat sky_vertex_data[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

static const GLfloat sky_uv_data[] = {
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f
};

static const GLfloat cube_vertex_data[] = {
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,

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

static const GLfloat cube_uv_data[] = {
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

GLFWwindow * window;

int main (int argc, char *argv[])
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
		fprintf(stderr, "Failed to initialize GLEW.\n");
		return -1;
	}

	GLuint shader[2], programD;
	prepareShader(shader, "shaders/vertex.vsh", GL_VERTEX_SHADER);
	prepareShader(shader + 1, "shaders/fragment.fsh", GL_FRAGMENT_SHADER);
	prepareProgram(&programD, shader, 2);

	object_data * skybox = malloc(sizeof(object_data));
	make_object(skybox, sizeof sky_vertex_data, sky_vertex_data, sky_uv_data, "skybox.jpg", programD);
	
	object_data * cube = malloc(sizeof(object_data));
	make_object(cube, sizeof cube_vertex_data, cube_vertex_data, cube_uv_data, "cube.jpg", programD);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window))
	{ glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox->projectionMatrix = m4_perspective(45.0f, (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		skybox->viewMatrix = m4_look_at(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		skybox->scalingMatrix = m4_scaling(vec3(100.0f, 100.0f, 1.0f));
		skybox->rotatingMatrix = m4_identity();
		skybox->translatingMatrix = m4_translation(vec3(0.0f, 0.0f, -80.0f));
		drawObject(skybox);

		cube->projectionMatrix = skybox->projectionMatrix;
		cube->viewMatrix = skybox->viewMatrix;
		cube->scalingMatrix = m4_identity();
		cube->rotatingMatrix = m4_rotation(deg_to_rad(30.0f), vec3(1.0f, 1.0f, 0.0f));
		cube->translatingMatrix = m4_identity();
		drawObject(cube);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
