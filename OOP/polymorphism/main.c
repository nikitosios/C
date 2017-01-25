#include <stdio.h>

typedef char type1;
typedef short type2;
typedef int type3;
typedef long type4;

#define typename(x) _Generic((x), \
		type1 : "type1", \
		type2 : "type2", \
		type3 : "type3", \
		type4 : "type4" \
)

int main (void)
{
	type1 A;
	type2 B;
	type3 C;
	type4 D;

	printf("A : %s,\nB : %s,\nC : %s,\nD : %s.\n",
			typename(A), typename(B), typename(C), typename(D));
	return 0;
}
