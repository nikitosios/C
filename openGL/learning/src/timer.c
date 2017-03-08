#include "header.h"

void timer (void)
{
	angle += ANGLE_STEP;
	if (angle >= 360.0f)
		angle = 0.0f;
	lastTime = time;
	return;
}