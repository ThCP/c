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
        exit(32);
    } else {
        // parent process
        wait(&status);
        printf("I am the parent process. My pid is = %d. My child's pid is %d. The return value of the child process is %d\n", getpid(), pid1, status>>8);
    }


    return 0;
}
