#ifndef SHADERS_H
#define SHADERS_H

char * loadShaderAsString (const char *);
void prepareShader (unsigned int *, const char *, int);
void prepareProgram (unsigned int *, unsigned int *, int);

#endif
