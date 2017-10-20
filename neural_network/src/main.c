#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Network.h"

int main (void)
{
	Network * net = new_Network();
	train(net);
	test(net);
	return 0;
}
