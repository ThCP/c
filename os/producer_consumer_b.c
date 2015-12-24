/*
	This is another example of producer-consumer realized using pipes and synchronization with signals.

	Author: Riccardo Cappuzzo
	2015-08-17
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define BUF_SIZE 128

void catcher(){};

int main () {
	int status, processed_bytes;
	pid_t producer, consumer;
	char buffer [BUF_SIZE+1];
	char input [BUF_SIZE+1];
	int pipe_fd[2];

	signal (SIGUSR1, catcher);

	if (pipe (pipe_fd) == -1) {
		fprintf(stderr, "Pipe error\n");
		exit(1);
	} else {
		consumer = fork ();
		if (consumer == 0) {
			// consumer child process
			while(1) {
				pause();
				processed_bytes = read (pipe_fd[0], buffer, BUF_SIZE);
				sscanf(buffer, "%d %s", &producer, input);
				printf("%s\n", input);
				if (strcmp (input, "end") == 0) {
					break;
				}		
				kill (producer, SIGUSR1);	
			}
			exit(0);
		} else {
			producer = fork ();
			if (producer == 0){
				// producer child process
				while (1) {
					
					printf("? ");
					scanf("%s", input);
					sprintf(buffer, "%d %s", getpid(), input);
					processed_bytes = write (pipe_fd[1], buffer, strlen(buffer)+1); 
					kill (consumer, SIGUSR1);
					if (strcmp (input, "end") == 0) {
						break;
					}
					pause();
				}
				exit(0);
			} else {
				// parent process
				waitpid(producer, &status, 0);
				waitpid(consumer, &status, 0);
			}
	
		}
	}
	return 0;

}
