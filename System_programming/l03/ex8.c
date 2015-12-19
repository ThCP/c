/**
	Write a multi-threaded program that evaluates the math series
	defined as sum of x^i for i going from 0 to N, where x
	and N are passed as input. 
	Each thread evaluats a single x^i instance, referring to
	its index of creation, and adds it to the final result.
	Once every thread completes its job, the main program 
	displays the final result.
	
	sysprog03
	
	Riccardo Cappuzzo
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h> // I am exploiting the math library for the pow function

// Allocation functions are needed since I don't know a priori
// the number of operations I'll have to execute.
pthread_t * allocate_tids ( int N );
struct args * allocate_args ( int N );
float * allocate_results( int N );

void * runner (void *arg);

struct args {
	int tid;
};

float base;
float *results;
float sum = 0;

int 
main (int argc, char *argv[])
{
	int N;
	int i;
	pthread_t *tids;
	struct args *args_array;
	
	if (argc != 3)
	{
		fprintf (stderr, "Wrong number of arguments\n");
		printf ("Correct usage: %s <base> <final exponent>\n", argv[0]);
		exit(1);
	}
		
	N = atoi(argv[2]); // Read the upper limit of the sum
	
	N = N+1; // so that the sum actually runs from 0 to N instead of from 0 to N-1
	
	if (N <=0)
	{
		fprintf (stderr, "The upper limit must be positive\n");
		exit(1);
	}
	
	sscanf(argv[1], "%f", &base);
	
	results = allocate_results(N);
	args_array = allocate_args(N);
	tids = allocate_tids(N);
		
	// Assign values to the args of the runner function
	for (i = 0; i < N; i += 1)
	{
		args_array[i].tid = i;
	}
	
	for (i = 0; i < N; i += 1)
	{
		if (pthread_create(&tids[i], NULL, runner, (void *) &args_array[i]))
		{
			fprintf (stderr, "Error during creation of a thread\n");
			exit(1);
		}	
	}
	
	for (i = 0; i < N; i += 1)
	{
		pthread_join(tids[i], NULL);
	}
	
	// This is not required
	for (i = 0; i < N; i += 1)
	{
		printf("The result of %g to the %d is %g\n", base, i, results[i]);
		sum+=results[i];
	}
	
	// Final result
	printf("The sum is %g\n", sum); 
	
	return 0;
}

void * runner (void * arg) {
	struct args * args;
	float exp;
	
	args = (struct args *) arg;
	exp = (float)args->tid;
	
	results[args->tid] = pow(base, exp);
	
	pthread_exit(NULL);
}

/* Allocation functions below, same as other exercises */
pthread_t * allocate_tids ( int N ){
	pthread_t *np_t;
	
	np_t = (pthread_t *) malloc (sizeof (pthread_t ) * N);
	
	if (np_t == NULL)
	{
		fprintf (stderr, "Error in allocation\n");
		exit(1);
	}
	
	return np_t;
}

struct args * allocate_args ( int N ) {
	struct args *np_s;

	np_s = (struct args *) malloc (sizeof (struct args) * N);
	
	if (np_s == NULL)
	{
		fprintf (stderr, "Error in allocation\n");
		exit(1);
	}
	
	return np_s;
}

float * allocate_results ( int N ) {
	float *np;

	np = (float *) malloc (sizeof (float) * N);
	
	if (np == NULL)
	{
		fprintf (stderr, "Error in allocation\n");
		exit(1);
	}
	
	return np;
}
