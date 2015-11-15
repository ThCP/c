/**
	Write a simple program able to do a fork() and then to print messages both
	from the father and the son processes. Finally modify the program in order to have the
	messages printed from the father only after the son is finished.

	Riccardo Cappuzzo
	
	s231643

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t pid1;
    int status;

    pid1 = fork();

    if (pid1 == 0) {
        // child process
        printf("I am the child process. My pid is = %d. My parent's pid is %d.\n", getpid(), getppid());
        sleep(2);
//        exit(0);
        exit(32); // arbitrary return value to show the result in the parent process
    } else {
        // parent process
        wait(&status); // wait for the child to end before printing the message
        printf("I am the parent process. My pid is = %d. My child's pid is %d. The return value of the child process is %d\n", getpid(), pid1, status>>8);
    }


    return 0;
}
