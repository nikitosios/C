/* file for "Lighting" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */

#include <GL/glut.h>
#include "api.h"

#define MOUSE_MOTION_STEP 0.2

unsigned short window_width = 800, window_height = 600;
float rotate_camera_x = 0.0, rotate_camera_y = 3.0;
unsigned int pyramidT;

unsigned int loadTextureFromFile(char* filename, int* w, int* h)
{
	unsigned int textureID;

	unsigned char *pixels = SOIL_load_image(filename, w, h, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *w, *h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	free(pixels);
	return textureID;
}

/* initializes 3D rendering */
void initGL(void) {
	int pyramidTW, pyramidTH;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0); /* enable light #0 */
	glEnable(GL_LIGHT1); /* enable light #1 */
	glEnable(GL_NORMALIZE); /* automatically normalize normals */
	/* glShadeModel(GL_SMOOTH); */ /* enable smooth shading */

	pyramidT = loadTextureFromFile("pyramid.jpg", &pyramidTW, &pyramidTH);
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

float angle = 0.0;

/* draws the 3D scene */
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0.0, 4.0, 5.0,
			rotate_camera_x, rotate_camera_y, 0.0,
			0.0, 1.0, 0.0);
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
	
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	drawCube(2.0);
	glRotatef(-angle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);

	glTranslatef(3.0, 1.1, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pyramidT);
	drawPyramidDown(1.0, 2.0, 2.0);
	glRotatef(-angle, 0.0, 1.0, 0.0);
	glTranslatef(-3.0, -1.1, 0.0);
	glDisable(GL_TEXTURE_2D);

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
	angle += 1.5;
	if (angle > 360)
		angle -= 360;
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char **argv) {
	/* initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	
	/* create the window */
	glutCreateWindow("Lighting - videotutorialsrock.com");
	initGL();
	
	/* set handler functions */
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutPassiveMotionFunc(passiveMMotion);
	glutTimerFunc(25, update, 0); /* add a timer */
	glutMainLoop();
	return 0;
}
