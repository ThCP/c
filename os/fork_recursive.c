/*
	This program creates n child processes, where each process creates its own child. When the level n
	is reached, the child sleeps t seconds before printing the value of count (which denotes the depth).
	
	Parameters passed on the command line: n (depth) and t (sleep time)

	Author: Riccardo Cappuzzo
	2015-08-15
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fork_recursive (int n, int t, int count);

int main (int argc, char *argv[]) {
	pid_t pid;
	int n, t;	
 	int count;	

	if (argc != 3) {
		fprintf(stderr, "Wrong number of arguments\n");
		exit(1);
	}
	
	n = atoi (argv[1]);
	t = atoi (argv[2]);

	fork_recursive (n, t, 0);

	return 0;

}

int fork_recursive (int n, int t, int count) {
	pid_t pid1, pid2;	
	
	if (n == 0) { // minimum level reached
		//count++;
		sleep(t);
		printf("Pid = %d counter = %d\n", getpid(), count);
		return n;
	}
	else {
		pid1 = fork();
		if (pid1 > 0){
			// parent process
			return (fork_recursive (n-1, t, count+1));
		} else {
			// child process
			return (fork_recursive (n-1, t, count+1));
		}
	}
}
