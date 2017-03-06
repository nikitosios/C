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
#include "geometry.h"

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

	GLuint vbo, vao;
	prepareTriangleBuffers(&vbo, &vao);

	mat4_t myMatrix = m4_translation(vec3(10.0, 0.0, 0.0));
	vec3_t myVector = vec3(10.0, 10.0, 10.0);
	vec3_t translatedVector = m4_mul_pos(myMatrix, myVector);

	mat4_t identityMatrix = m4_identity();
	vec3_t someVector = vec3(1.0, 2.0, 3.0);
	vec3_t anotherVector = m4_mul_dir(identityMatrix, someVector);

	mat4_t scalingMatrix = m4_scaling(vec3(2.0, 2.0, 2.0));
	vec3_t xVector = vec3(5.0, 6.0, 7.0);
	vec3_t scaledXVector = m4_mul_pos(scalingMatrix, xVector);

	vec3_t myRotationAxis = vec3(2.0, 3.0, 4.0);
	mat4_t myRotatedAxis = m4_rotation(45.0, myRotationAxis);

	vec3_t originalVector = vec3(1.0, 2.0, 3.0);
	mat4_t translationMatrix = m4_translation(vec3(10.0, 0.0, 0.0));
	mat4_t rotationMatrix = m4_rotation(15.0, myRotationAxis);
	mat4_t scaleMatrix = m4_scaling(vec3(1.5, 1.5, 2.0));
	/* далее: сначала выполняется масштабирование, потом поворот,
	 * и только потом выполняется перенос */
	vec3_t transformedVector1 = m4_mul_pos(translationMatrix,
			m4_mul_pos(rotationMatrix, m4_mul_pos(scaleMatrix, originalVector)));
	/* вариант получше (порядок все еще важен): */
	mat4_t myModelMatrix = m4_mul(translationMatrix, m4_mul(rotationMatrix, scaleMatrix));
	m4_print(myModelMatrix);
	vec3_t transformedVector2 = m4_mul_pos(myModelMatrix, originalVector);

	mat4_t projectionMatrix = m4_perspective(45.0f,
			(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, NEAR_VIEW_DISTANCE, FAR_VIEW_DISTANCE);
	mat4_t viewMatrix = m4_look_at(vec3(4.0, 3.0, 3.0), vec3(0.0, 0.0, 0.0),
			vec3(0.0, 1.0, 0.0));
	mat4_t modelMatrix = m4_mul(translationMatrix, m4_mul(rotationMatrix, scaleMatrix));
	mat4_t MVP = m4_mul(projectionMatrix, m4_mul(viewMatrix, modelMatrix));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		prepareTriangle(programD);
		glUseProgram(programD);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
