#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

#define BUF_SIZE 1024

int main (int argc, char ** argv) {
	
	int finn, fout;
	//FILE * finn, *fout;
	char buffer[BUF_SIZE], *tok;
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
		fout = creat (argv[2], 0622);
		if (fout == -1) {
			fprintf (stderr, "Output file could not be created.\n");
			exit(1);
		} else {
			while ( (count = read (finn, buffer, BUF_SIZE) > 0) ){
				if (buffer[strlen(buffer)-2] == '\n') {
					buffer[strlen(buffer)-2] = '\0';
				}
				
				tok = strtok(buffer, "\n");
				while (tok != NULL) {
					number = atoi(tok);
					printf("%d \n", number);
					
					tok = strtok (NULL, "\n");
				}
				
				
			}
			close (fout);
		}
		close (finn);
	}
	
	return 0;

}
	
