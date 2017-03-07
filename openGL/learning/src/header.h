#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math_3d.h"
#include "constants.h"
#include "shaders.h"

extern GLuint programD;
extern GLFWwindow * window;
extern mat4_t projectionMatrix, viewMatrix, modelMatrix, MVP;
extern mat4_t translationMatrix, rotationMatrix, scalingMatrix;

#endif
