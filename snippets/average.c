#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv) {
	int count = 0, sum = 0, res, n;
	float average;
	FILE * finn;
	
	if (argc != 2) {
		fprintf (stderr, "Wrong number of arguments.\nCorrect usage: %s FILENAME\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	finn = fopen (argv[1], "r");

	if (finn == NULL) {
		fprintf (stderr, "File %s not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	while ( (res = fscanf(finn, "%d ", &n)) > 0) {
		count++;
		sum+=n;
	}
	
	average = (float) sum / (float) count;
	
	fclose(finn);
	
	printf("Average = %f\n", average);
	
	//return 0;
	exit(EXIT_SUCCESS);
}
