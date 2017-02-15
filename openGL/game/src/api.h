#ifndef API_H
#define API_H

#include <SOIL/SOIL.h>
#include <GL/glut.h>

#define drawCube(a) drawBox(a, a, a)

void drawBox(float, float, float);
void drawPyramid(float, float);
void drawPyramidDown(float, float, float);
void drawEye(float, unsigned int);
float *multipleVectors(float *, float *);

#endif
