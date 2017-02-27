/* file for "Lighting" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include "api.h"

#define MOUSE_MOTION_STEP 0.08
#define WINDOW_TITLE "MLG game by Nikitosios"

char *progdir;
unsigned short window_width = 800, window_height = 600;
float rotate_camera_x = 2.0, rotate_camera_y = 3.0;
unsigned int pyramidT, eyeT;
int pyramidTW, pyramidTH, eyeTW, eyeTH;
float angle = 0.0;

unsigned int loadTextureFromFile(char* filename, int* w, int* h)
{
	unsigned int textureID;
	unsigned char *pixels;
	char buffer[256];
	char bytes;
   
	bytes = strlen(progdir);
	memcpy(buffer, progdir, bytes - 1);
	buffer[bytes - 1] = '/';
	memcpy(buffer + bytes, filename, strlen(filename) + 1);
	printf("loading texture %s\n", buffer);

	pixels = SOIL_load_image(buffer, w, h, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *w, *h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	/* glGenerateMipmap(GL_TEXTURE_2D); */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	SOIL_free_image_data(pixels);
	return textureID;
}

/* initializes 3D rendering */
void initGL(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0); /* enable light #0 */
	glEnable(GL_LIGHT1); /* enable light #1 */
	glEnable(GL_NORMALIZE); /* automatically normalize normals */
	/* glShadeModel(GL_SMOOTH); */ /* enable smooth shading */

	pyramidT = loadTextureFromFile("pyramid.jpg", &pyramidTW, &pyramidTH);
	eyeT = loadTextureFromFile("eye.png", &eyeTW, &eyeTH);
	return;
}

/* called when the window is resized */
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
	return;
}

/* draws the 3D scene */
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(1.0, 4.0, 0.8,
			rotate_camera_x, rotate_camera_y, 0.0,
			0.0, 1.0, 0.0);
	glTranslatef(-0.5, 0.0, 7.0);
	glTranslatef(0.0, 0.0, -8.0);
	
	/* add ambient light */
	GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	/* add positioned light */
	GLfloat lightColor0[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat lightPos0[] = { 4.0, 0.0, 8.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	/* add directed light */
	GLfloat lightColor1[] = { 0.5, 0.2, 0.2, 1.0 };
	/* coming from the direction (-1, 0.5, 0.5) */
	GLfloat lightPos1[] = { -1.0, 0.5, 0.5, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glTranslatef(0.0, -0.05, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	drawBox(500.0, 0.1, 500.0);
	glTranslatef(0.0, 0.05, 0.0);
	
	drawMLGPyramid();
	
	glutSwapBuffers();
}

void passiveMMotion(int x, int y)
{
	static int last_x, last_y;

	if (x - last_x > 10)
		rotate_camera_x += MOUSE_MOTION_STEP;
	if (x - last_x < -10)
		rotate_camera_x -= MOUSE_MOTION_STEP;
	if (y - last_y > -10)
		rotate_camera_y -= MOUSE_MOTION_STEP;
	if (y - last_y < 10)
		rotate_camera_y += MOUSE_MOTION_STEP;
	if (abs(x - last_x) > 10)
		last_x = x;
	if (abs(y - last_y) > 10)
		last_y = y;
	return;
}

void update(int value) {
	/* angle += 1.5; */
	if (angle > 360)
		angle -= 360;
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char **argv) {
	int i;

	for (i = strlen(argv[0]) - 1; argv[0][i] != '/'; --i);
	progdir = malloc(i + 2);
	memcpy(progdir, argv[0], i);
	progdir[i] = '/';
	progdir[i + 1] = '\0';

	/* initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	
	/* create the window */
	glutCreateWindow(WINDOW_TITLE);
	initGL();
	
	/* set handler functions */
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutPassiveMotionFunc(passiveMMotion);
	glutTimerFunc(25, update, 0); /* add a timer */
	glutMainLoop();
	return 0;
}
