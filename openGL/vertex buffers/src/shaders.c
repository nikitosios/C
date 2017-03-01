#include <GL/gl.h>

GLuint prepareProgram (char* errorFP)
{
	*errorFP = GL_FALSE;

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	*errorFP = checkProgramLinkStatus(programId);
	if (*errorFP) return 0;

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}
