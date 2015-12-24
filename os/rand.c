/* 
	This program writes a file which contains N numbers randomly generated.
	
	The arguments passed on the command line are the name of the output file and
	the number of values to be generated. An optional third argument defines the
	range of the values (from 0 to MAX). Defaults to 10000.
	
	Syntax: rand OUTPUT_FILE NUMBERS_PRODUCED [MAX_VALUE] 
	
	Author: Riccardo Cappuzzo
	2015-08-19
*/

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
	int N, i, max;
	FILE * fout;
	
	if ((argc != 3) && (argc != 4)) {
		fprintf( stderr, "Wrong number of parameters\n");
		exit(1);
	}
	
	fout = fopen (argv[1], "w");
	
	if (fout == NULL) {
		fprintf(stderr, "Error during the creation of the output file.\n");
		exit(1);
	}
	
	N = atoi (argv[2]); // fetch the number of values to generate
	 
	max = (argc == 4) ? atoi(argv[3]) : 10000; // set the range (0-max)

	//printf("max is %d\n", max);

	fprintf(fout, "%d\n", N);	// print the number of values on the first row
	
	for (i = 0; i < N; i++) { // print on file the values
		fprintf(fout, "%d\n", rand() % max); 
	}
	
	return 0;

}
	
		
		
		
