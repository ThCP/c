/*
	Basic example of parent-child synchronization with wait() function
	
	Author: Riccardo Cappuzzo
	
	2015-08-15
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv[]){
	pid_t pid;
	int sleep_time = 0;
	int status, return_code;	

	pid = fork();

	if (argc != 2) {
		fprintf (stderr, "Wrong number of arguments\n");
		exit(1);
	}

	sleep_time = atoi(argv[1]);	

	if (pid == 0) {
		printf("This is the child. Child pid = %d Parent pid = %d \n", getpid(), getppid());
		/* work done inside the child process */
		printf("Insert a return code\n");
		scanf("%d", &return_code);
		sleep (sleep_time);
		exit (return_code);		
	}
	else {
		printf("This is the parent. pid = %d\n", getpid());
		pid = wait (&status);
		printf("The return code of process %d is %d\n", pid, status>>8);
	}

	return 0;

}

	
	
