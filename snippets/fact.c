#include <stdlib.h>
#include <stdio.h>

long factorial ( long val );

int main (int argc, char ** argv) {

	long val, res;
	
	val = atol(argv[1]);
	
	res = factorial(val);
	printf("factorial of %ld is %ld\n", val, res);

	return 0;
}


long factorial (long val) {
    long i, c = 1;

    if ((val == 0) || (val == 1))
        return 1;
    else {
        for (i = 2; i <= val; i++) {
            c*=i;
        }
    }

    return c;
}

