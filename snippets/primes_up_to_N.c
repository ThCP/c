#include <stdlib.h>
#include <stdio.h>

/* This program receives as an input parameter N on the command line a number
	and computes all the first N primes, storing them in the file 
	"primes_N.list".

	Author: Riccardo Cappuzzo
	2015-10-31
*/
	
int main (int argc, char ** argv) {
	long number;
	long i, last;
	int prime = 1;
	FILE * fd;
	long count = 0;
	
	last = atol(argv[1]); // read the parameter
	
	if (last < 2) {
		fprintf(stderr, "Incorrect input value, min = 2\n");
		exit (1);
	}

	fd = fopen("primes_N.list", "w"); // create the output file
	
	for (number = 2; count < last; number++) {
		
		if (number == 2) prime = 1; 
		else if (number % 2 == 0)  { // this effectively halves the number of checks
			continue;
		}
		for ( i = 3; i <= number/i; i+=2 ) { // increment by 2 skips all even divisors
			if  (number%i == 0) { // number isn't prime
				prime = 0;
				break;
			} 
		}
		
		if (prime) {
			// prime numbers are written on file
			fprintf(fd, "%ld\n", number);
			count++;
		} 
		prime = 1;
	}
	
	fclose (fd); // close output file
	return 0;

}
