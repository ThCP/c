#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
	long number;
	long i;
	int prime = 1;
	
	number = atol(argv[1]);	

	if (number < 1) {
		printf("The number must be positive.\n");
		exit(1);
	}

	if (number == 2) prime = 1;
	for ( i = 2; i <= number/i; i++ ) {
		if  (number%i == 0) { 
			prime = 0;
			break;
		} 
	}

	if (prime) {
		printf("The number %ld is prime.\n", number);
	} else {
		printf("The number %ld is not prime, its first divisor is %ld\n", number, i);
	}

	return 0;

}
