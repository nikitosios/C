#include <GL/freeglut.h>

#define WINDOW_TITLE "My game"

unsigned short window_width = 800, window_height = 600;

/* Имена всех функций, предоставляемых непосредственно OpenGL, начинаются с приставки gl. */
/* Функции, задающие некоторый параметр, характеризующийся набором чисел (например координату или цвет),
 * имеют суффикс вида [число параметров + тип параметров + представление параметров]. */
/* Число параметров — указывает число принимаемых параметров. Принимает следующие значения: 1, 2, 3, 4 */
/* Тип параметров — указывает тип принимаемых параметров.
 * Возможны следующие значения: b, s, i, f, d, ub, us, ui.
 * Т.е. byte (char в C, 8-битное целое число),
 * short (16-битное целое число),
 * int (32-битное целое число),
 * float (число с плавающей запятой),
 * double (число с плавающей запятой двойной точности),
 * unsigned byte, unsigned short, unsigned int (последние три — беззнаковые целые числа) */
/* Представление параметров — указывает в каком виде передаются параметры,
 * если каждое число по отдельности, то ничего не пишется,
 * если же параметры передаются в виде массива, то к названию функции дописывается буква v */
/* Пример: glVertex3iv задает координату вершины, состоящую из трех целых чисел, передаваемых в виде указателя на массив. */

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* GL_POINTS — каждая вершина задает точку */
/* GL_LINES — каждая отдельная пара вершин задает линию */
/* GL_LINE_STRIP — каждая пара вершин задает линию
 * (т.е. конец предыдущей линии является началом следующей) */
/* GL_LINE_LOOP — аналогично предыдущему за исключением того,
 * что последняя вершина соединяется с первой и получается замкнутая фигура */
/* GL_TRIANGLES — каждая отдельная тройка вершин задает треугольник */
/* GL_TRIANGLE_STRIP — каждая следующая вершина задает треугольник
 * вместе с двумя предыдущими (получается лента из треугольников) */
/* GL_TRIANGLE_FAN — каждый треугольник задается первой вершиной и последующими парами
 * (т.е. треугольники строятся вокруг первой вершины, образуя нечто похожее на диафрагму) */
/* GL_QUADS — каждые четыре вершины образуют четырехугольник */
/* GL_QUAD_STRIP — каждая следующая пара вершин образует четырехугольник вместе с парой предыдущих */
/* GL_POLYGON — задает многоугольник с количеством углов равным количеству заданных вершин */

/* glColor* — задает цвет всех примитивов до следующего glColor* */
/* glVertex* — задает вершину */

void display(void)
{
	float angle = 45;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(0, 0);
	glVertex2i(100, 0);
	glVertex2i(100, 100);
	glVertex2i(0, 100);
	glVertex2i(300, 400);
	glVertex2i(300, 300);
	glVertex2i(400, 300);
	glVertex2i(400, 400);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{

	/* void glutDisplayFunc (void (*func) (void)) — задает функцию рисования изображения */
	/* void glutReshapeFunc (void (*func) (int width, int height)) — задает функцию обработки изменения размеров окна */
	/* void glutVisibilityFunc (void (*func)(int state)) — задает функцию обработки изменения состояния видимости окна */
	/* void glutKeyboardFunc (void (*func)(unsigned char key, int x, int y)) — задает функцию обработки нажатия клавиш клавиатуры
	 * (только тех, что генерируют ascii-символы) */
	/* void glutSpecialFunc (void (*func)(int key, int x, int y)) — задает функцию обработки нажатия клавиш клавиатуры
	 * (тех, что не генерируют ascii-символы) */
	/* void glutIdleFunc (void (*func) (void)) — задает функцию, вызываемую при отсутствии других событий */
	/* void glutMouseFunc (void (*func) (int button, int state, int x, int y)) — задает функцию, обрабатывающую команды мыши */
	/* void glutMotionFunc (void (*func)(int x, int y)) — задает функцию, обрабатывающую движение курсора мыши,
	 * когда зажата какая-либо кнопка мыши */
	/* void glutPassiveMotionFunc (void (*func)(int x, int y)) — задает функцию, обрабатывающую движение курсора мыши,
	 * когда не зажато ни одной кнопки мыши */
	/* void glutEntryFunc (void (*func)(int state)) — задает функцию, обрабатывающую движение курсора за пределы окна и его возвращение */
	/* void glutTimerFunc (unsigned int msecs, void (*func)(int value), value) — задает функцию, вызываемую по таймеру	 */

	glutInit(&argc, argv);
	/* Включаем двойную буферизацию и четырехкомпонентный цвет */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(window_width, window_height);
	glutCreateWindow(WINDOW_TITLE);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
