/* file for "Lighting" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */

#include <GL/glut.h>
#include "api.h"

unsigned short window_width = 800, window_height = 600;

/* initializes 3D rendering */
void initGL(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0); /* enable light #0 */
	glEnable(GL_LIGHT1); /* enable light #1 */
	glEnable(GL_NORMALIZE); /* automatically normalize normals */
	/* glShadeModel(GL_SMOOTH); */ /* enable smooth shading */
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

float angle = -70.0;

/* draws the 3D scene */
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
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
	
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	drawCube(2.0);

	glutSwapBuffers();
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
	glutTimerFunc(25, update, 0); /* add a timer */
	glutMainLoop();
	return 0;
}
