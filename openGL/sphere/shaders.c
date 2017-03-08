#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>

char * loadShaderAsString (const char * filename)
{
	char * shader, *shaderbak;
	FILE * shaderfile;
	int shaderfilesize;

	shaderfile = fopen(filename, "r");
	if (shaderfile <= 0)
	{
		fprintf(stderr, "Shader file %s do not exists.\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(shaderfile, 0, SEEK_END);
	shaderfilesize = ftell(shaderfile);
	fseek(shaderfile, 0, SEEK_SET);

	shader = (char*) malloc(shaderfilesize);
	for (int i = 0; i < shaderfilesize; ++i)
		shader[i] = fgetc(shaderfile);

	if (shader[shaderfilesize - 1] == EOF)
		shader[shaderfilesize - 1] = '\0';
	else if (shader[shaderfilesize - 1] != '\0')
	{
		shaderbak = (char*) malloc(shaderfilesize + 1);
		memcpy(shaderbak, shader, shaderfilesize);
		shaderbak[shaderfilesize] = '\0';
		return shaderbak;
	}

	fclose(shaderfile);
	return shader;
}

void prepareShader (unsigned int * shaderD, const char * shaderfilename, int shaderType)
{	
	*shaderD = glCreateShader(shaderType);
	if (*shaderD == 0)
	{
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	const char * shaderCode = loadShaderAsString((char*) shaderfilename);
	const char * codeArray[] = {shaderCode};
	glShaderSource(*shaderD, 1, codeArray, NULL);

	glCompileShader(*shaderD);

	int result;
	glGetShaderiv(*shaderD, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		fprintf(stderr, "Vertex shader compilation failed!\n");

		int logLen;
		glGetShaderiv(*shaderD, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = (char*) malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(*shaderD, logLen, &written, log);

			fprintf(stderr, "Shader log:\n%s", log);
			free(log);
			exit(EXIT_FAILURE);
		}
	}

	return;
}

void prepareProgram (unsigned int * programD,
		unsigned int * shaders, int n)
{
	*programD = glCreateProgram();
	if (*programD == 0)
	{
		fprintf(stderr, "Error creating program object.\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (i < n)
	{
		glAttachShader(*programD, shaders[i]);
		++i;
	}

	glLinkProgram(*programD);

	int status;
	glGetProgramiv(*programD, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		fprintf(stderr, "Failed to link shader program!\n");

		int logLen;
		glGetProgramiv(*programD, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = (char*) malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(*programD, logLen, &written, log);
			fprintf(stderr, "Program log:\n%s", log);
			free(log);
			exit(EXIT_FAILURE);
		}
	}
}
