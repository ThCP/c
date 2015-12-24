/* 
	Simple example of synchronization with signals.

	Author: Riccardo Cappuzzo
	2015-08-17	

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void catcherp(){};
void catcherc(){};

int main() {
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		// child process
		signal(SIGUSR1, catcherc);
		while (1) {
			sleep(3); 
			printf("I am the child process\n");
			kill (getppid(), SIGUSR2);
			pause();
		}
	} else {
		// parent
		signal(SIGUSR2, catcherp);
		while (1) {
			sleep(3);
			printf("I am the parent process\n");
			kill(pid, SIGUSR1);
			pause();
		}
	}

	return 0;

}
