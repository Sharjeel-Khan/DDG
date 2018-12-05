#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long int fact(int x)
{
	long int r = x;
	while (--x >=2)
		r *= x;

	return r;
}

int main(int argc, char **argv)
{
	int a = atoi(argv[1]);

	printf("fact: %lu\n", fact(a));

	return 0;
}
