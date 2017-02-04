#include <stdio.h>

int main (const int argc, const char ** const argv)
{
	char rights[] = "r";
	FILE *fd;
	char buf;

	fd = fopen(argv[1], rights);
	while ((buf = getc(fd)) != EOF)
		putc(buf, stdout);
	fclose(fd);
	return 0;
}

