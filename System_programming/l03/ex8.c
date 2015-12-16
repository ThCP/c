#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

pthread_t * allocate_tids ( int N );
struct args * allocate_args ( int N );
float * allocate_results( int N );
void * runner (void *arg);

struct args {
	int tid;
	float base;
};

float *results;
float sum = 0;

int 
main (int argc, char *argv[])
{
	float x;
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
		
	N = atoi(argv[2]);
	
	N = N+1;
	
	if (N <=0)
	{
		fprintf (stderr, "The upper limit must be positive\n");
		exit(1);
	}
	
	sscanf(argv[1], "%f", &x);
	
	results = allocate_results(N);
	args_array = allocate_args(N);
	tids = allocate_tids(N);
	
	for (i = 0; i < N; i += 1)
	{
			args_array[i].tid = i;
			args_array[i].base = x;
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
	
	for (i = 0; i < N; i += 1)
	{
		printf("The result of %f to the %d is %f\n", x, i, results[i]);
	}
	
	printf("The sum is %f\n", sum);
	
	return 0;
}

void * runner (void * arg) {
	struct args * args;
	float exp;
	
	args = (struct args *) arg;
	exp = (float)args->tid;
	
	results[args->tid] = pow(args->base, exp);
	sum=sum+pow(args->base, exp);
	
	pthread_exit(NULL);
}


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
