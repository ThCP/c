/* 
	ex11
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_VALUE 5
#define BUF_LEN 128


int main(int argc, char ** argv)
{
    int i, n, val, status;
    pid_t pids[MAX_VALUE];
    int sum = 0;
    int fd[2];
    char buffer[BUF_LEN+1];
    int count_pipe;

    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    n = atoi (argv[1]);

    if (n < 1) {
        fprintf(stderr, "Number must be larger than 0\n");
        exit(EXIT_FAILURE);
    }

    if (n > MAX_VALUE) {
        fprintf(stderr, "Number must be smaller than %d\n", MAX_VALUE);
        exit(EXIT_FAILURE);
    }

    if ((pipe(fd)) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }


    for (i = 1; i <= n; i++) {
        pids[i-1] = fork();

        if (pids[i-1] == 0) {
            // child process

            val = (int) pow(2, i);

            sprintf(buffer, "%d", val);
            count_pipe = write(fd[1], buffer, strlen(buffer)+1);

            if (count_pipe == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        } else {
            // parent process

            waitpid(pids[i-1], &status, 0);
            count_pipe = read(fd[0], buffer, BUF_LEN);

            if (count_pipe == -1) {
                fprintf(stderr, "parent error %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            sscanf(buffer, "%d", &val);
            sum+=val;
            printf("sum = %d\n", sum);
        }

    }

    printf("The sum is %d\n", sum);


    return 0;
}
