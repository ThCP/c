/**
	
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * reader (void * arg);
void * listener (void * arg);

int counter = 0; // counter is shared among all the threads

pthread_mutex_t lock; // lock is shared among all the threads

int 
main (int argc, char *argv[])
{
	pthread_t tid1, tid2, tid3, tid4;
	
	// initialize the mutex 
	pthread_mutex_init (&lock, NULL);

	// create the reader process, which receives from stdin the value to add to the counter		
	if (pthread_create(&tid1, NULL, reader, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}

	// create the 3 listener processes, which check the value of the counter and decrease it 
	if (pthread_create(&tid2, NULL, listener, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}
	if (pthread_create(&tid3, NULL, listener, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}
	if (pthread_create(&tid4, NULL, listener, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}
	
	// join all the threads
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	
	// destroy the mutex
	pthread_mutex_destroy(&lock);
		
	return 0;
}

void * reader (void * arg) {
	int val;
	while (scanf("%d", &val)>0) // read from input 
	{
		pthread_mutex_lock(&lock); // increase the counter value, I need a mutex
									// in order to avoid concurrent access
		counter+=val;
		pthread_mutex_unlock(&lock); // free the mutex
	}
	pthread_exit(NULL);
}

void * listener (void * arg) {
	pthread_t tid = pthread_self();

	while (1)
	{	
		//		
		if (counter > 0)
		{
			pthread_mutex_lock (&lock);			
			counter--; 
			printf("Tid = %d counter value = %d\n", (int) tid, counter);
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
	}
	pthread_exit(NULL);
}
