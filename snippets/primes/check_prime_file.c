#include <stdlib.h>
#include <stdio.h>
	
int main (int argc, char ** argv) {
	long i, last;
	int prime = 1;
	FILE * fd;
	long count = 0;
	
	last = atol(argv[1]); // read the parameter
	
	if (argc != 2) {
		fprintf(stderr, "Not enough arguments\n");
		exit (1);
	}

	fd = fopen(argv[1], "r"); // create the output file
	
	while (fscanf(fd, "%ld", &last) != EOF)
	{
		if (last == 2) prime = 1; 
		else if (last % 2 == 0)  { // this effectively halves the number of checks
			printf ("Number %ld is not prime\n", last);
			continue;
		}
		for ( i = 3; i <= last/i; i+=2 ) { // increment by 2 skips all even divisors
			if  (last%i == 0) { // number isn't prime
				printf ("Number %ld is not prime\n", last);
				prime = 0;
				count++;
				break;
			} 
		}
		
		prime = 1;
	}
	
	printf("Found %ld nonprime numbers.\n", count);
		
	fclose (fd); // close output file
	return 0;

}
