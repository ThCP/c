/**
	Write a multi-threaded program to search if a number N is 
	prime by checking if it is divisible by any number in the
	range [2, N/2]. 
	The program receives in input the number N and the number
	of threads to use P.
	Each thread checks a subset of the interval.
	As soon as a thread detects that the number isn't prime,
	the threads stop.
	
	sysprog03
	
	Riccardo Cappuzzo 

*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int prime = 1; // flag for detecting non-prime numbers
				// numbers are prime until a divisor is found

struct args {
	long start; // start of the subset of the interval
	long end; // end of the subset of the interval
	long N; // input number
};
	
void * runner (void *arg); 
struct args * allocate_struct ( int P );
pthread_t * allocate_tids ( int P );

int 
main (int argc, char *argv[])
{
	int P; // number of threads
	long N; // number to check
	pthread_t *tids;
	struct args *args_array;
	long q; // quotient
	int i;
	
	if (argc != 3)
	{
		fprintf (stderr, "Wrong number of arguments\n");
		printf ("Correct usage: %s <input number> <number of threads to use>\n", argv[0]);
		exit(1);
	}
	
	N = atol(argv[1]); // fetch the input number
	
	if (N <=0)
	{
		fprintf (stderr, "The input number must be positive\n");
		exit(1);
	}
	
	P = atoi(argv[2]); //fetch the number of threads
	
	if (P <=0)
	{
		fprintf (stderr, "The number of threads must be positive\n");
		exit(1);
	}
	
	if (P > N) 
	{
		fprintf (stderr, "The number of threads must be smaller than the input number\n");
		exit(1);
	}
	
	q = (N/2)/(long)P; // find the width of the intervals
	
	args_array = allocate_struct ( P );
	tids = allocate_tids ( P );
	
	/* the following instructions are used to define the sub-intervals among the P threads */
	for (i = 0; i < P; i += 1)
	{
			args_array[i].start = q*i+1;
			args_array[i].end = q*(i+1);
			args_array[i].N = N;
	}
	args_array[i-1].end = N/2+(N%2);
	args_array[0].start = 2;

	/* threads are created and start running */
	for (i = 0; i < P; i += 1)
	{
		if (pthread_create(&tids[i], NULL, runner, (void *) &args_array[i]))
		{
			fprintf (stderr, "Error during creation of a thread\n");
			exit(1);
		}	
	}
	
	/* the main thread waits the end of the runner threads */
	for (i = 0; i < P; i += 1)
	{
		pthread_join(tids[i], NULL);
	}
	
	if (prime == 1)
	{
		printf("The number is prime.\n");
	} else {
		printf ("The number isn't prime.\n");
	}
	
	return 0;
}

void * runner (void * arg) {
	struct args * args;
	int i;
	
	args = (struct args *) arg;
	
	for (i = args->start; i < args->end && prime != 0; i += 1)
	{
		if ((args->N % i) == 0 || prime == 0)
		{
			prime = 0;
			printf("%d is a divisor\n", i);
			pthread_exit(NULL);
		}
	}
	pthread_exit(NULL);
}

pthread_t * allocate_tids ( int P ){
	pthread_t *np_t;
	
	np_t = (pthread_t *) malloc (sizeof (pthread_t ) * P);
	
	if (np_t == NULL)
	{
		fprintf (stderr, "Error in allocation\n");
		exit(1);
	}
	
	return np_t;
}

struct args * allocate_struct ( int P ) {
	struct args *np_s;

	np_s = (struct args *) malloc (sizeof (struct args) * P);
	
	if (np_s == NULL)
	{
		fprintf (stderr, "Error in allocation\n");
		exit(1);
	}
	
	return np_s;
}
