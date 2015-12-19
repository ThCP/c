
/* This program receives as an input parameter N on the command line a number
	and computes all the first N primes, storing them in the file 
	"primes_threads.list".

	Author: Riccardo Cappuzzo
	2015-10-31
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * runner (void *arg);

struct args * allocate_struct ( int P );
pthread_t * allocate_tids ( int P );

struct args {
	long long start; // start of the subset of the interval
	long long last;
	FILE *fd;
};	

pthread_mutex_t lock;

int P;

long long count = 0;

int main (int argc, char ** argv) {
	long long i, last;
	FILE * fd;
	pthread_t *tids;
	struct args *args_array;
	
	pthread_mutex_init (&lock, NULL);
	
	if (argc != 3)
	{
		fprintf (stderr, "Wrong number of arguments.\nUsage %s <limit> <number of threads>\n", argv[0]);
		exit(1);
	}
	
	last = atol(argv[1]); // read the parameter
	
	if (last < 2) {
		fprintf(stderr, "Incorrect input value, min = 2\n");
		exit (1);
	}
	
	P = atoi(argv[2]); //fetch the number of threads
	
	if (P <=0)
	{
		fprintf (stderr, "The number of threads must be positive\n");
		exit(1);
	}
	
	if (P > last) 
	{
		fprintf (stderr, "The number of threads must be smaller than the input number\n");
		exit(1);
	}

	fd = fopen("primes_threads.list", "w"); // create the output file
	
	if (fd == NULL)
	{
		fprintf (stderr, "Error in file creation\n");
		exit(1);
	}
	
	fprintf(fd, "%d\n", 2);
	
	args_array = allocate_struct ( P );
	tids = allocate_tids ( P );
	
	for (i = 0; i < P; i += 1)
	{
			args_array[i].start = i;
			args_array[i].last = last;
			args_array[i].fd = fd;
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
	
	for (i = 0; i < P; i += 1)
	{
		pthread_join(tids[i], NULL);
	}
	
	fclose (fd); // close output file
	return 0;

}

void * runner (void *arg)
{
	struct args * args;
	long long i;
	int prime = 1;
	long long start, last, number;
	FILE * fd;
	
	args = (struct args *) arg;
	fd = args->fd;
	start = args->start;
	last = args->last;
	
	
	for (number = 3+start; count < last; number+=P) {
		if (number % 2 == 0)  { // this effectively halves the number of checks
			continue;
		}
		for ( i = 3; i <= number/i; i+=2 ) { // increment by 2 skips all even divisors
			if  (number%i == 0) { // number isn't prime
				prime = 0;
				break;
			} 
		}
		
		if (prime) {
			// prime numbers are written on file
			pthread_mutex_lock (&lock);
			fprintf(fd, "%lld\n", number);
			count++;
			pthread_mutex_unlock (&lock);
		} 
		prime = 1;
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
