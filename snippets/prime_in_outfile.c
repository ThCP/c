#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
	long number;
	long i, last;
	int prime = 1;
	FILE * fd;
	
	last = atol(argv[1]);

	fd = fopen("primes.list", "w");
	
	for (number = 2; number < last; number++) {
		
		if (number == 2) prime = 1;
		else if (number % 2 == 0)  {
			continue;
		}
		for ( i = 3; i <= number/i; i+=2 ) {
			if  (number%i == 0) { 
				prime = 0;
				break;
			} 
		}
		
		if (prime) {
			fprintf(fd, "%ld\n", number);
		} 
		prime = 1;
	}
	
	fclose (fd);
	return 0;

}
