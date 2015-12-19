/*
	This program takes as an input a number and checks whether it is prime or not.
	
	Riccardo Cappuzzo
*/

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
	long long number;
	long long i;
	int prime = 1;
	
	number = atol(argv[1]);	

	if (number < 1) {
		printf("The number must be positive.\n");
		exit(1);
	}

	if (number == 2) 
	{	
		prime = 1;
		i = 2;
	}
	
	else if (number == 3)
	{ 
		i = 3;
		prime = 1;
	}
	else if (number % 2 == 0)
	{
		i = 2;
		prime = 0;
	}
	else
	{
		for ( i = 3; i <= number/i; i+=2 ) {
			if  (number%i == 0) { 
				prime = 0;
				break;
			} 
		}
	}

	if (prime) {
		printf("The number %lld is prime.\n", number);
	} else {
		printf("The number %lld is not prime, its first divisor is %lld\n", number, i);
	}
	
	printf("Loop ended at iteration %lld\n", i);

	return 0;

}
