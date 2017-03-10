#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/* #include <assimp/cimport.h> */
/* #include <assimp/scene.h> */
/* #include <assimp/postprocess.h> */
#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"
#include "shaders.h"

typedef struct {
	float x;
	float y;
} vec2_t;

void d (int d)
{
	printf("%i: all right.\n", d);
	return;
}

char loadOBJ (const char * path, vec3_t * out_vertices,
		vec3_t * out_normals)
{
	unsigned int * vertexIndices, * normalIndices;
	vec3_t * temp_vertices;
	vec3_t * temp_normals;
	int size;

	FILE * file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Can not load OBJ file.\n");
		return GL_FALSE;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	temp_vertices = malloc(size * sizeof(vec3_t));
	temp_normals = malloc(size * sizeof(vec3_t));

	vertexIndices = malloc(size);
	normalIndices = malloc(size);

	int v = 0, n = 0;
	int vi = 0, ni = 0;
	char lineHeader[128];
	int res;

	while (1)
	{
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			vec3_t vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices[v++] = vertex;
		} else if (strcmp(lineHeader, "vn") == 0) {
			vec3_t normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals[n++] = normal;
		} else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",
					&vertexIndex[0], &normalIndex[0],
					&vertexIndex[1], &normalIndex[1],
					&vertexIndex[2], &normalIndex[2]);
			if (matches != 6)
			{
				printf("File can't be read by our simple parser: (Try exporting with other options)\n");
				return GL_FALSE;
			}

			vertexIndices[vi++] = vertexIndex[0];
			vertexIndices[vi++] = vertexIndex[1];
			vertexIndices[vi++] = vertexIndex[2];
			normalIndices[ni++] = normalIndex[0];
			normalIndices[ni++] = normalIndex[1];
			normalIndices[ni++] = normalIndex[2];
		}
	}

	out_vertices = malloc((vi - 1) * sizeof(vec3_t));
	out_normals = malloc((ni - 1) * sizeof(vec3_t));

	int ov = 0, ou = 0, on = 0;
	for (unsigned int i = 0; i < vi; ++i)
	{
		unsigned int vertexIndex = vertexIndices[i];
		vec3_t vertex = temp_vertices[vertexIndex - 1];
		out_vertices[ov++] = vertex;
	}

	for (unsigned int i = 0; i < ni; ++i)
	{
		unsigned int normalIndex = normalIndices[i];
		vec3_t normal = temp_normals[normalIndex - 1];
		out_normals[on++] = normal;
	}

	free(temp_vertices);
	free(temp_normals);

	free(vertexIndices);
	free(normalIndices);

	return vi - 1;
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

	vec3_t * vertices;
	vec3_t * normals;
	char res = loadOBJ("model.obj", vertices, normals);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, res * sizeof(vec3_t), vertices,
			GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, res * sizeof(vec3_t),
			(void*)0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	mat4_t projection, view, model, MVP;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programD);

		unsigned int MVPpos;
		MVPpos = glGetUniformLocation(programD, "MVP");

		MVP = m4_perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
		MVP = m4_mul(MVP, m4_look_at(vec3(0.0f, 0.0f, 3.0f),
					vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
		model = m4_identity();
		MVP = m4_mul(MVP, model);

		glUniformMatrix4fv(MVPpos, 1, GL_FALSE, (float *) &MVP);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glDrawArrays(GL_TRIANGLES, 0, 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
