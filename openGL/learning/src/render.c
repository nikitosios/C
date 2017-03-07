#include "header.h"

static const GLfloat cube_data[] = {
	/* front */
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	/* back */
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	/* left */
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	/* right */
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	/* up */
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	/* down */
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
};

void render (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projectionMatrix = m4_perspective(45.0f,
			(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
			NEAR_VIEW_DISTANCE, FAR_VIEW_DISTANCE);
	viewMatrix = m4_look_at(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0, 1.0, 0.0));
	rotationMatrix = m4_rotation(90.0f, vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = m4_identity();
	MVP = m4_mul(projectionMatrix, m4_mul(viewMatrix, modelMatrix));

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof cube_data, cube_data,
			GL_STATIC_DRAW);

	GLint posLoc, posCol, posMVP;
	GLint vertexSize = 3 * sizeof(float);

	posLoc = glGetAttribLocation(programD, "position");
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE,
			vertexSize, (void*)0);
	glEnableVertexAttribArray(posLoc);

	posMVP = glGetUniformLocation(programD, "MVP");
	glUniformMatrix4fv(posMVP, 1, GL_FALSE, (const GLfloat *) &MVP);

	glUseProgram(programD);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 12*3);

	glfwSwapBuffers(window);
	glfwPollEvents();


}
