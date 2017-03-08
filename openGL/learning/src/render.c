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

static const GLfloat cube_color_data[] = {
	/* front */
	1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	/* back */
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	/* left */
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	/* right */
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	/* up */
	1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	/* down */
	0.0, 1.0, 1.0,
	0.0, 1.0, 1.0,
	0.0, 1.0, 1.0,
	0.0, 1.0, 1.0,
	0.0, 1.0, 1.0,
	0.0, 1.0, 1.0
};

void render (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projectionMatrix = m4_perspective(45.0f,
			(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
			NEAR_VIEW_DISTANCE, FAR_VIEW_DISTANCE);
	viewMatrix = m4_look_at(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0, 1.0, 0.0));
	rotationMatrix = m4_rotation(angle, vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = rotationMatrix;
	MVP = m4_mul(projectionMatrix, m4_mul(viewMatrix, modelMatrix));

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof cube_data, cube_data,
			GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof cube_color_data, cube_color_data,
			GL_STATIC_DRAW);

	GLint posLoc, posCol, posMVP;
	GLint vertexSize = 3 * sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	posLoc = glGetAttribLocation(programD, "position");
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE,
			vertexSize, (void*)0);
	glEnableVertexAttribArray(posLoc);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	posCol = glGetAttribLocation(programD, "color");
	glVertexAttribPointer(posCol, 3, GL_FLOAT, GL_FALSE,
			vertexSize, (void*)0);
	glEnableVertexAttribArray(posCol);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	posMVP = glGetUniformLocation(programD, "MVP");
	glUniformMatrix4fv(posMVP, 1, GL_FALSE, (const GLfloat *) &MVP);

	glUseProgram(programD);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 12*3);

	glfwSwapBuffers(window);
	glfwPollEvents();
}