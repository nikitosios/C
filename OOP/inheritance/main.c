#include <stdio.h>
#include <stdlib.h>

typedef struct point2D {
	int x,y;
} point2D;

typedef struct point3D {
	struct point2D;
	int z;
} point3D;

struct point3D *newPoint3D (void);

struct point3D *newPoint3D (void)
{
	struct point3D *st;

	st = malloc(sizeof(struct point3D));
	st->x = 1;
	st->y = 2;
	st->z = 3;
	return st;
}

int main() {
	point3D *point = newPoint3D();
	printf("x = %d,\ny = %d,\nz = %d\n", point->x, point->y, point->z);
	return 0;

}
