#include <stdio.h>

int main (const int const argc, const char ** argv)
{
	FILE *fi, *fo;
	unsigned long size;

	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "w");
	fseek(fi, 0, SEEK_END);
	size = ftell(fi);
	fseek(fi, 0, SEEK_SET);
	for (long i = 0; i < size; i++)
		putc(getc(fi), fo);
	fclose(fi);
	fclose(fo);
	return 0;
}

