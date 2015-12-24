/* 
	This program reads from a file whose name is passed on the
	command line a list of commands	and then executes them using
	the "system() function. Each command is executed using a child process.
	The parent sleeps for n seconds, where n read on the command line. 

	Author: Riccardo Cappuzzo
	2015-08-17	

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_MAX 256+1 // length of the buffer string

int main (int argc, char ** argv) {
	pid_t pid; // needed to create the processes
	FILE *finn;	 // input file
	int n; // sleep time
	char buffer[BUFFER_MAX];

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
		pid = fork (); // create a child process
		if (pid == 0) {
			// child process
			printf("####################\n%s", buffer); // print the read command
			system (buffer); // execute the command
			exit(0); // exit with correct status
		}	else {
			wait(); // wait for the end of the child process
			sleep(n); // sleep for n seconds
		}
	}

	fclose(finn);	//close the input file

	return 0; // end of program

}
