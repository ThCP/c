/*
    Exercise 11
    Given an input command line parameter n, this program computes the sum of
    all the powers of 2 starting from 2^1 up to 2^n. It uses a pipe and multiple
    child processes, each computing its value of 2^n.

	Riccardo Cappuzzo
	
	s231643

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
    int i, n;
    int status;
    double val;
    double sum = 0;
    pid_t pids[MAX_VALUE];
    int fd[2];
    char buffer[BUF_LEN+1];
    int count_pipe;

    /*
        ERROR CHECKS
    */
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

    /*
        END ERROR CHECKS
    */

    for (i = 1; i <= n; i++) {
        pids[i-1] = fork(); // I use n processes

        if (pids[i-1] == 0) {
            // child process
            val = pow(2, i);

            sprintf(buffer, "%f", val);
            count_pipe = write(fd[1], buffer, strlen(buffer)+1); // write on pipe

            if (count_pipe == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        } else {
            // parent process
            count_pipe = read(fd[0], buffer, BUF_LEN); // read from pipe

            if (count_pipe == -1) {
                fprintf(stderr, "parent error %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            sscanf(buffer, "%lf",&val);
            sum+=val;
        }

    }
    printf("The sum is %f\n", sum);

    return 0;
}
