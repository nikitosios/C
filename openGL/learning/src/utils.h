#ifndef UTILS_H
#define UTILS_H

void render (void);
void timer (void);
char * loadShaderAsString (const char *);
void prepareShader (unsigned int *, const char *, int);
void prepareProgram (unsigned int *, unsigned int *, int);

#endif