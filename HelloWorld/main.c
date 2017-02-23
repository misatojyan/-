#include <stdio.h>

int f(int n)
{
	int s = 1;
	for (int i = 1; i <= n; i++)
	{
		s *= i;
	}
	return s;
}

int main()
{
	fprintf(stdout, "Hello World!\n");
	printf("%d\n", f(5));
}