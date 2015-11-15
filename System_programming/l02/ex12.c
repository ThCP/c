/*
    Exercise 12
    This exercise computes the Taylor expansion of the exponential function
    defined as

    exp(x) = 1 + sum(x^i/i!)
    with i going from 1 to N

    N and x are values passed as inputs where x is a double number and N is larger than 0.

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

#define BUF_LEN 128

long factorial (long val);

int main(int argc, char ** argv)
{
    int i, N;
    double val;
    double sum = 1;
    double x;
    pid_t pid;
    int fd[2];
    char buffer[BUF_LEN+1];
    int count_pipe;

    /*
        ERROR CHECKS
    */
    if (argc != 3) {
        fprintf(stderr, "Wrong number of arguments\n");
        printf("Usage: %s x N\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi (argv[2]);

    sscanf(argv[1], "%lf", &x);

    if (N < 0) {
        fprintf(stderr, "Number must be positive or 0\n");
        exit(EXIT_FAILURE);
    }

    if ((pipe(fd)) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /*
        END ERROR CHECKS
    */

    for (i = 1; i <= N; i++) {
        pid = fork();
        if (pid == 0) {
            // child process
            val = pow(x, i) / ((double)factorial(i));

            sprintf(buffer, "%f", val);
            count_pipe = write(fd[1], buffer, strlen(buffer)+1); // write on pipe

            if (count_pipe == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            printf("Step %d: val = %lf\n", i, val);
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
    printf("The result is %lf\n", sum);

    return 0;
}


long factorial (long val) {
    long i, c = 1;

    if ((val == 0) || (val == 1))
        return 1;
    else {
        for (i = 2; i <= val; i++) {
            c*=i;
        }
    }

    return c;
}
