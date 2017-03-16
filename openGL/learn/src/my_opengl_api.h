#ifndef MY_OPENGL_API_H
#define MT_OPENGL_API_H

#include <stdlib.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include "math_3d.h"
#include "shaders.h"

typedef struct {
	GLuint program, vbo, vao, uvbo, texture;
	GLuint vbo_size, matrixID, textureID;
	mat4_t projectionMatrix, viewMatrix, modelMatrix;
	mat4_t translatingMatrix, rotatingMatrix, scalingMatrix;
	mat4_t MVP;
} object_data;

GLuint loadTexture (const char * filename)
{
	GLuint texture;
	GLint w, h;
	void * pixels;

	pixels = SOIL_load_image(filename, &w, &h, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data((unsigned char *) pixels); 
	return texture;
}

void make_object (object_data * object, const GLuint sizeof_vertex_data,
		const GLfloat * vertex_data, const GLfloat * uv_data,
		const char * texture_filename, const GLuint programD)
{
	GLuint sizeof_uv_data = sizeof_vertex_data / 3.0f * 2;
	object->program = programD;
	glGenVertexArrays(1, &object->vao);
	glBindVertexArray(object->vao);
	glGenBuffers(1, &object->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof_vertex_data, vertex_data, GL_STATIC_DRAW);
	glGenBuffers(1, &object->uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, object->uvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof_uv_data, uv_data, GL_STATIC_DRAW);
	object->vbo_size = sizeof_vertex_data;
	glUseProgram(object->program);
	object->matrixID = glGetUniformLocation(object->program, "MVP");
	object->textureID = glGetUniformLocation(object->program, "myTextureSampler");
	object->texture = loadTexture(texture_filename);
}

void drawObject (object_data * object)
{
		object->modelMatrix = m4_mul(object->translatingMatrix, m4_mul(object->rotatingMatrix, object->scalingMatrix));
		object->MVP = m4_mul(object->projectionMatrix, m4_mul(object->viewMatrix, object->modelMatrix));

		glUseProgram(object->program);

		glUniformMatrix4fv(object->matrixID, 1, GL_FALSE, (GLfloat *) &object->MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->texture);
		glUniform1i(object->textureID, 0);

		glBindVertexArray(object->vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, object->uvbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, object->vbo_size / sizeof(float));

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}

#endif
