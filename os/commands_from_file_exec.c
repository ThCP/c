/* 
	This program reads from a file whose name is passed on the command 
	line a list of commands	and then executes them using the exec family
	of functions. Each command is executed using a child process. The
	parent sleeps for n seconds, where n read on the command line. 

	Author: Riccardo Cappuzzo
	2015-08-17	
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_MAX 256+1 // length of the buffer string

int main (int argc, char ** argv) {
	pid_t pid; // needed to create the processes
	FILE *finn;	 // input file
	int n, i; // sleep time
	char buffer[BUFFER_MAX];
	char command [64+1];
	int n_commands = 0;
	char * b_commands;
	char *command_matrix[10];
	
	if (argc != 3) { // check number of command line arguments
		fprintf (stderr, "Wrong number of arguments\n");
		exit(1);
	}

	n = atoi(argv[2]);	// fetch the sleep time

	finn = fopen (argv[1], "r"); // open file in read mode

	if (finn == NULL) {
		fprintf (stderr, "Error in opening the input file\n"); 
		exit(1);
	}

	while (fgets (buffer, BUFFER_MAX, finn) != NULL) { // keeps looping until eof is reached
		// printf("%s", buffer); // print the command
		buffer[strlen(buffer)-1] = '\0'; // skip the last \n
		b_commands = strtok (buffer, " ");	 // split the buffer
		for (n_commands = 0; b_commands != NULL; n_commands++){	
			command_matrix[n_commands] = b_commands; // copy the pointer towards the token in the matrix
			// printf("%s\n", command_matrix[i]); // print the command
			b_commands = strtok(NULL, " "); // proceed to the next token of the string
		}
		//printf ("number of commands = %d\n", n_commands);
		command_matrix[n_commands] = (char*)0; // set the last entry in the command matrix to a NULL pointer
		
		pid = fork (); // create a child process
		if (pid == 0) {
			// child process

			/* execvp is used
				v -> stands for "variable", I use an array of variables
				p -> stands for "path", I search in the PATH environment variable
				command_matrix[0] is used to parse the name of the command to look for in the PATH
				command_matrix contains the arguments
			*/	

			execvp (command_matrix[0], command_matrix); 
			exit(0); // exit with correct status
		}	else { // parent process
			wait(); // wait for the end of the child process
			sleep(n); // sleep for n seconds
		}

		
	}

	fclose(finn);	//close the input file

	return 0; // end of program

}

