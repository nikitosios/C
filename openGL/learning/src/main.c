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

int main (void)
{
	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
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

	mat4_t projectionMatrix, viewMatrix, modelMatrix, MVP;
	mat4_t translationMatrix, rotationMatrix, scalingMatrix;

	static const GLfloat cube_data_without_colors[] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		projectionMatrix = m4_perspective(45.0f,
				(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, NEAR_VIEW_DISTANCE, FAR_VIEW_DISTANCE);
		viewMatrix = m4_look_at(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f),
				vec3(0.0, 1.0, 0.0));
		translationMatrix = m4_translation(vec3(0.0f, 0.0f, 3.0f));
		rotationMatrix = m4_rotation(45.0f, vec3(0.0, 1.0, 0.0));
		scalingMatrix = m4_scaling(vec3(2.0, 2.0, 2.0));
		mat4_t modelMatrix = m4_mul(translationMatrix, m4_mul(rotationMatrix, scalingMatrix));
		mat4_t MVP = m4_mul(projectionMatrix, m4_mul(viewMatrix, modelMatrix));

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof cube_data_without_colors,
				cube_data_without_colors, GL_STATIC_DRAW);

		GLint posLoc, posCol, posMVP;
		GLint vertexSize = 3 * sizeof(float);

		posLoc = glGetAttribLocation(programD, "position");
		glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE,
				vertexSize, (void*)0);
		glEnableVertexAttribArray(posLoc);

		posCol = glGetUniformLocation(programD, "color");
		glUniform3f(posCol, 1.0f, 0.0f, 0.0f);

		posMVP = glGetUniformLocation(programD, "MVP");
		glUniformMatrix4fv(posMVP, 1, GL_FALSE, (const GLfloat *) &MVP);

		glUseProgram(programD);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 12*3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
