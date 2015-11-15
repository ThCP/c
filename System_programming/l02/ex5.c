/**
	Write a C program able to run the following Unix commands:
	cp /etc/passwd .
	sort passwd –o mypasswd
	cat mypasswd

	Riccardo Cappuzzo
	
	s231643

*/

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
        execl("/bin/cp", "cp", "/etc/passwd", ".", (char *) 0); // execl requires the abs. path to the source code of the command
    } else {
        // parent process
        waitpid(pid1, &status, 0);
        pid1 = fork();

        if (pid1 == 0) {
            //child process
            execlp("sort", "sort", "passwd", "-o", "mypasswd", (char * ) 0); // execlp requires only the command name
 			fprintf(stderr, "Exec failed\n"); // exec should never return to the calling function
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
