/*
	Write a C program in which the parent process creates two child processes, 
	a producer and a consumer. The producer reads a line of text from stdin 
	and writes it to a file. The consumer process waits for data to be 
	written by the producer and once data is available reads data from the file.
	Once a line is read by the consumer it shows the text line. When the 
	producer reads “end” the program terminates.

	Author: Riccardo Cappuzzo
	2015-08-17
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void catcher(){};

int main () {
	int status_consumer, status_producer; // needed for the waitpid functions
	pid_t producer, consumer; // pids of the child processes
	char string[128]; // input string
	FILE * f; // fp
	
	signal (SIGUSR1, catcher);
	
	consumer = fork();
	if (consumer == 0) { 
		// child process
		while (1) {		
			pause(); // wait for the ready signal from the sender
			f = fopen ("tmp.txt", "r");
			fscanf (f, "%d %s", &producer, string); // read string and the pid of the sender
			printf("%s\n", string);   
			fclose(f); 
			
			if (strcmp("end", string) == 0) {
				break; // exit the loop when the word "end" is read
			}
			kill (producer, SIGUSR1);		
		}
		
		exit(0);
	} else {
		producer = fork (); 
		if (producer == 0) {
			// child process
			while(1) { 		
				f = fopen ("tmp.txt", "w");
				printf("?: ");
				scanf("%s", string); // read from stdin the string
				fprintf(f, "%d\t%s\n", getpid(), string); // write on tmp.txt the string
				fclose(f);
				
				kill(consumer, SIGUSR1);
				if (strcmp("end", string) == 0){
					break; // exit the loop when the word "end" is read
				}			
				pause();
			}
		} else {
			// parent process
			waitpid(producer, &status_producer, 0);
			waitpid(consumer, &status_consumer, 0);
		}
	
	}
	return 0;  // end of program
}
