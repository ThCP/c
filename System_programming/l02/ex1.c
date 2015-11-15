/**
	ex1	
	
	Write a C program able to read a list of integer numbers from a text file
	(whose name is given as a first command line parameter) printing on another text
	file (whose name is given as a second command line parameter) only the numbers
	that are prime. Please use the appropriate UNIX system calls for reading and writing files.

	sysprog2
	
	Riccardo Cappuzzo
	s231643

*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

#define BUF_SIZE 1024

int check_prime (int number);

int main (int argc, char ** argv) {
	
	int finn, fout;
	char buf_int[BUF_SIZE], buf_out[BUF_SIZE], *tok;
	int number, count;
	
	if (argc != 3) { 
		fprintf (stderr, "Wrong number of arguments.\n");
		exit(1);
	}
	
	finn = open (argv[1], O_RDONLY);
	
	if (finn == -1) {
		fprintf (stderr, "Input file does not exist.\n");
		exit(1);
	} else {
		fout = creat (argv[2], 0622); //create the output file
		if (fout == -1) {
			fprintf (stderr, "Output file could not be created.\n");
			exit(1);
		} else {
			while ( (count = read (finn, buf_int, BUF_SIZE) > 0) ){ //read the input file
			
				if (buf_int[strlen(buf_int)-2] == '\n') { // remove the last \n character
					buf_int[strlen(buf_int)-2] = '\0';
				}
				
				tok = strtok(buf_int, "\n"); // divide the string line by line
				while (tok != NULL) {
					number = atoi(tok); // read the number
					
					if (check_prime (number)) { 
						sprintf(buf_out, "%d\n", number); 
						write(fout, buf_out, (int) strlen(buf_out));
						printf("%d \n", number);
					}
					tok = strtok (NULL, "\n");
				}
			}
			close (fout);
		}
		close (finn);
	}
	
	return 0;

}	

// sieve, this can be improved
// return 1 for prime numbers, 0 otherwise
int check_prime (int number) {
	int i;
	
	if (number == 2) return 1;
	
	if (number%2 == 0) return 0;
	
	for (i = 3; i < number/2; i++) {
		if (number%i == 0) return 0;
	}
	return 1;
}

