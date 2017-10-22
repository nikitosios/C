#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Network.h"

int main (void)
{
	Network * net = new_Network();
	printf("Done.\n");
	train(net);
	printf("Done.\n");
	test(net);
	printf("Done.\n");
	return 0;
}
