#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1;
    int status;

    pid1 = fork();

    if (pid1 == 0) {
        // child process
        execl("/bin/cp", "cp", "/etc/passwd", ".", (char *) 0);
    } else {
        // parent process
        waitpid(pid1, &status, 0);
        pid1 = fork();

        if (pid1 == 0) {
            //child process
            execlp("sort", "sort", "passwd", "-o", "mypasswd", (char * ) 0);
        } else {
            //parent process
            waitpid(pid1, &status, 0);
            pid1 = fork();

            if (pid1 == 0) {
                // child process
                execlp("cat", "cat", "mypasswd", (char *) 0);
            }
            waitpid(pid1, &status, 0);

            printf("Completed.\n");
        }

    }

    return 0;
}
