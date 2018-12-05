#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long int fact(int x)
{
	long int r = x;
	while (x >= 2){
		x = x - 1;
		r *= x;
	}


	return r;
}

int main(int argc, char **argv)
{
	int a = atoi(argv[1]);
    int b = atoi(argv[2]);
	if(a > 0){
	    printf("fact: %lu\n", fact(b));
	}
	return 0;
}
