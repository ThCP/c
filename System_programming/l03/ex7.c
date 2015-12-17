/**
	Write a program with 10 threads. Threads are numbered from 0-9 and receiver their order number from the main program.
	Each thread generates a random number in the range 1-10 and stores it in a shared array in the position indicated by its order number.
	
	sysprog03
	
	Riccardo Cappuzzo
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h> // used for the srand function

#define N_THREADS 10 //defines the number of threads I'm using
#define RAND_LIMIT 10 // defines the width of the interval

int results[N_THREADS]; // shared array

pthread_t * allocate_tids ( int N ); // allocates a variable size array of tids
void * runner (void * arg); // routine called by the threads

int 
main (int argc, char *argv[])
{
	pthread_t *tids;
	int sum = 0;
	int i;
	
	srand(time(NULL)); // changes the seed at each iteration
	
	tids = allocate_tids(N_THREADS); // allocates the array of tids
	
	for (i = 0; i < N_THREADS; i += 1)
	{
		if (pthread_create(&tids[i], NULL, runner, (void *) &i)) // creates the threads
		{
			fprintf (stderr, "Error during creation of a thread\n");
			exit(1);
		}	
	}
	
	
	for (i = 0; i < N_THREADS; i += 1) // joins the threads
	{
		pthread_join(tids[i], NULL);
	}
	
	for (i = 0; i < N_THREADS; i += 1) // computes the sum
	{
		printf("results[%d] = %d\n", i, results[i]);
		sum+=results[i];
	}
	printf("The sum is %d\n", sum);
	
	return 0;
}

void * runner (void * arg) {
	int *tid;
	
	tid = (int *) arg;
	
	results[*tid] = rand() % RAND_LIMIT +1; // random values generated here are not randomly distributed
	
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
