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
	long long start; // start of the subset of the interval
	long long end; // end of the subset of the interval
	long long N; // input number
};
	
void * runner (void *arg); 
struct args * allocate_struct ( int P );
pthread_t * allocate_tids ( int P );

int 
main (int argc, char *argv[])
{
	int P; // number of threads
	long long N; // number to check
	pthread_t *tids;
	struct args *args_array;
	long long q; // quotient
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
	
	if (N == 1)
	{
		printf ("The number %d isn't prime.\n", 1);
		return 0;
	}
	
	if (N %2 == 0 && N != 2)
	{
		printf ("2 is a divisor.\n");
		printf ("The number %lld isn't prime.\n", N);
		return 0;
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
	
	q = (N/2)/(long long)P; // find the width of the intervals
	
	args_array = allocate_struct ( P );
	tids = allocate_tids ( P );
	
	/* the following instructions are used to define the sub-intervals among the P threads */
	args_array[0].start = 2;
	args_array[0].end = args_array[0].start+q;
	args_array[0].N = N;
	
	for (i = 1; i < P; i += 1)
	{
			args_array[i].start = args_array[i-1].end+1;
			args_array[i].end = args_array[i].start+q;
			args_array[i].N = N;
	}
	
	for (i = 0; i < P; i += 1)
	{
		printf("s = %lld e = %lld\n", args_array[i].start, args_array[i].end);
	}
	
	
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
		printf("The number %lld is prime.\n", N);
	} else {
		printf ("The number %lld isn't prime.\n", N);
	}
	
	return 0;
}

void * runner (void * arg) {
	struct args * args;
	long long i;
	
	args = (struct args *) arg;
	if (args->start % 2 == 0) args->start++;
	for (i = args->start; i <= args->end && prime != 0; i += 2) // 
	{
		if ((args->N % i) == 0 && (args->N != i))
		{
			prime = 0;
			printf("%lld is a divisor\n", i);
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
