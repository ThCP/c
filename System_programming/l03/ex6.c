#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * reader (void * arg);
void * listener (void * arg);

int counter = 0;
pthread_mutex_t lock1, lock2;



int 
main (int argc, char *argv[])
{
	pthread_t tids[4];
	int i;

	pthread_mutex_init (&lock1, NULL);	
	pthread_mutex_init (&lock2, NULL);	
		
	i=0;
	/*
	if (pthread_create(&tids[0], NULL, reader, (void *) & i))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}
	
	//pthread_join (tids[0], NULL);
	
	//return 0;
	
	*/
	
	for (i = 1; i < 4; i += 1)
	{	//printf("creating listener threads\n");
		printf("i = %d\n", i);
		if (pthread_create(&tids[i], NULL, listener, (void *) &i))
		{
			fprintf (stderr, "Error while creating a thread.\n");
			exit(1);					
		}
	}
	
	while (1)
	{
		printf("Insert a counter value: ");
		scanf("%d", &val);
		
		counter+=val; 
		
	}
	
	for (i = 1; i < 4; i++) {
		pthread_join(tids[i], NULL);
	}
	
	pthread_mutex_destroy(&lock1);
		
	return 0;
}

void * reader (void * arg) {
	int val, *a;
	a = (int * ) arg;
	printf("reader arg = %d\n", *a);
	while (1)
	{
		pthread_mutex_lock(&lock1);
		printf("Insert a counter value: ");
		scanf("%d", &val);
		
		counter+=val; 
		pthread_mutex_unlock(&lock2);
	}
	pthread_exit(NULL);
}

void * listener (void * arg) {
	int i;
	int * tid;
	
	tid = (int *) arg;
	while (1)
	{	
		while (counter > 0)
		{
			pthread_mutex_lock (&lock2);			
			counter--; 
			printf("Tid = %d counter value = %d\n", *tid, counter);
			sleep(2);
			pthread_mutex_unlock(&lock1);
		}
	}
	pthread_exit(NULL);
}
