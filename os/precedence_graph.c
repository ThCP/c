/* 
	Precedence graph.
	
	Author: Riccardo Cappuzzo
	2015-08-17	

*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main () {
	pid_t p1, p2, p3, p4;	

	printf("p1, pid = %d\n", getpid());
	p1 = fork ();
	if (p1 == 0) {
		// child process
		printf ("p2, pid = %d\n", getpid());
		p2 = fork();
		if (p2 == 0) {
		// child
		printf("p4, pid = %d\n", getpid());
		exit(0);
		} else {
			// parent
			printf("p5, pid = %d\n", getpid());
			waitpid (p2, 0,0);
			printf("p8, pid = %d\n", getpid());
			exit(0);	
		}
	} else {
		// parent process
		printf ("p3, pid = %d\n", getpid());
		p3 = fork();
		if (p3 == 0){
			//child
			printf("p6, pid = %d\n", getpid());
			exit(0);
		} else {
			//parent
			printf("p7, pid = %d\n", getpid());
			waitpid(p3, 0, 0);
			printf("p9, pid = %d\n", getpid());
			waitpid(p1, 0, 0);
			printf("p10, pid = %d\n", getpid());
		}
	}
	
	return 0;	

}
	
