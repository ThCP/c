/* 
	ex11bis
	
	version with wait
	BAD SOLUTION
	HORRIBLE SOLUTION
	
	Same problem as ex11, but solved using the return value of the child processes.
	
	Riccardo Cappuzzo
	
	s231643
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

#define MAX_VALUE 5

int main(int argc, char ** argv)
{
    int i, n, val, status;
    pid_t pids[MAX_VALUE];
    int sum = 0;

    n = atoi (argv[1]);

    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        exit(1);
    }

    if (n < 1) {
        fprintf(stderr, "Number must be larger than 0\n");
        exit(1);
    }

    if (n > MAX_VALUE) {
        fprintf(stderr, "Number must be larger than %d\n", MAX_VALUE);
        exit(1);
    }


    for (i = 1; i <= n; i++) {
        pids[i-1] = fork();

        if (pids[i-1] == 0) {
            // child process
            val = (int) pow(2, i);
            exit(val);
        } else {
            // parent process
            waitpid(pids[i-1], &status, 0);
            sum+=(status>>8);
        }

    }
    printf("The sum is %d\n", sum);


    return 0;
}
