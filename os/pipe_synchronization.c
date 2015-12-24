/* 
	This program realizes the following precedence graph:
			A
		+---+----+
		B	|	 D
		|	C	 |
		| +-+-+  |
		| |	  |	 |
		| E	  F	 |
		| |	  |	 |
		| +-+-+  |
		| 	G	 H
		|  	|	 |
		+---+----+
			|
			I
	
	Multiple processes are created and synchronization is achieved by means of pipes.
	
	Author: Riccardo Cappuzzo
	2015-08-20
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUFLEN 2

int main () {
	int pipe_C[2], pipe_D[2], pipe_E[2];
	pid_t C, D, E;
	char junk[BUFLEN] = "x";
	
	if (pipe (pipe_C) == -1) {
		fprintf(stderr, "Error in creation of pipe_C\n");
		exit(1);
	}
	
	if (pipe (pipe_D) == -1) {
		fprintf(stderr, "Error in creation of pipe_D\n");
		exit(1);
	}
	
	if (pipe (pipe_E) == -1) {
		fprintf(stderr, "Error in creation of pipe_E\n");
		exit(1);
	}
	
	
	D = fork ();
	if (D == 0) {
		// child process, inside D
		write(pipe_D[1], junk, BUFLEN);
		exit(0);
	} else {
		C = fork();
		if (C == 0) {
			//child process, inside C
			E = fork ();
			if (E == 0) {
				// child process, inside E
				write(pipe_E[1], junk, BUFLEN);
				exit(0);
			} else {
				//  child process, inside F
				read(pipe_E[0], junk, BUFLEN);
				printf("read from pipe E\n");
				write(pipe_C[1], junk, BUFLEN);
				exit(0);
			}
		} else {
			// parent process, inside B
			read(pipe_C[0], junk, BUFLEN);
			printf("read from pipe_C\n");
			read(pipe_D[0], junk, BUFLEN);
			printf("read from pipe_D\n");
			printf("returning\n");
		}
	}
	
	return 0;

}
		
		
		
		
			
			
