#include <stdio.h>

int main (void)
{
	unsigned short count = 0;
	FILE *fd;

	printf("Введите кол-во символов, которые нужно прочитать: ");
	scanf("%i", &count);
	printf("Вывод:\n");
	fd = fopen("/etc/fstab", "r");
	for (unsigned char i = 0; i < count; i++)	
		printf("%c", fgetc(fd));
	fclose(fd);
	printf("\nКонец вывода.\n");
	return 0;
}

