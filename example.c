#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	char buffer[100], op[3], num[11];
	int i, it, a;
	char c;
	
	for (i = 0; i < sizeof(buffer); ++i)
	{
		c = getchar();
		if (c == '\n')
		{
			buffer[i] = '\0';
			break;
		}
		buffer[i] = c;
	}
	
	for (i = 0; buffer[i] == ' '; ++i);
	if (strncmp(buffer + i, "sqrt(x)", 7)
		&& strncmp(buffer + i, "sqrtx", 5)
		&& strncmp(buffer + i, "sqrtX", 5))
		return 1;

	for (; buffer[i] != '>' && buffer[i] != '<'; ++i);
	
	it = 0;
	for (; buffer[i] != ' '; ++i)
	{
		op[it] = buffer[i];
		++it;
	}
	op[it] = '\0';
	
	for (; buffer[i] == ' '; ++i);
	it = 0;
	for (; buffer[i] != ' ' && buffer[i] != '\0'; ++i)
	{
		num[it] = buffer[i];
		++it;
	}
	num[it] = '\0';

	a = atoi(num);
	if (a < 0)
	{
		if (*op == '<')
		{
			printf("Решений нет.\n");
			return 0;
		} else {
			a = 0;
			op[1] = '=';
			op[2] = '\0';
		}
	}
	a *= a;

	srand(time(NULL));

	switch (*op)
	{
		case '>':
			if (op[1] == '=')
			{
				printf("Интервал: [%i, бесконечность)\n", a);
				i = rand() % 10000 + a;
				printf("Например: %i, т.к.\nsqrt(%i) = %f\n", i,
						i, sqrt((double)i));
				return 0;
			}
			printf("Интервал: (%i, бесконечность)\n", a);
			i = rand() % 10000 + a + 1;
			printf("Например: %i, т.к.\nsqrt(%i) = %f\n", i,
					i, sqrt((double)i));
			return 0;
			break;
		case '<':
			if (op[1] == '=')
			{
				printf("Интервал: [0, %i]\n", a);
				i = rand() % ++a;
				printf("Например: %i, т.к.\nsqrt(%i) = %f\n", i,
						i, sqrt((double)i));
				return 0;
			}
			if (a == 0)
			{
				printf("Решений нет.\n");
				return 0;
			}
			printf("Интервал: [0, %i)\n", a);
			i = rand() % a;
			printf("Например: %i, т.к.\nsqrt(%i) = %f\n", i,
					i, sqrt((double)i));
			return 0;
			break;
	}

	return 0;
}
