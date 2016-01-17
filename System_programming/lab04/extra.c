/**
	This program generates up to 4 players using threads, where 1 of them reads from the LDD
	while the others attempt to update a number from the LDD, flipping a virtual coin to 
	decide whether to increase or decrease that number by 1, after reading the value of the
	LDD. 
	
	The connection to the LDD is a shared good and as such the access to it is protected by
	means of a mutex lock.

	sysprog04

	Riccardo Cappuzzo
*/


#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_NAME "/dev/my_device" // name of the device created 
#define BUFLEN 1024 // needed to read the values using the read system call

void * reader (void * arg); // this player reads from the device
void * updater (void * arg); // this player tries to update the device
int reading_value_of_device (void); // this function returns the current value of the device
void writing_on_device (int new); // this function writes the value new on the device
int coin_toss (void); 

pthread_mutex_t lock; // needed to protect the device from concurrent access

int 
main (int argc, char *argv[])
{
	pthread_t tid1, tid2, tid3, tid4; // ids of the threads
	
	// initialize the mutex 
	pthread_mutex_init (&lock, NULL);

	// create the reader process, which receives from stdin the value to add to the counter		
	if (pthread_create(&tid1, NULL, reader, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}

	// create the 3 updater processes, which check the value of the counter and decrease it 
	if (pthread_create(&tid2, NULL, updater, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}
	if (pthread_create(&tid3, NULL, updater, NULL))
	{
		fprintf (stderr, "Error while creating a thread.\n");
		exit(1);					
	}
	if (pthread_create(&tid4, NULL, updater, NULL))
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

// routine for the reader player
void * reader (void * arg)
{
	int val; // value read from the device
	// this while goes on forever
	while (1)
	{
		// reserving the access to the device
		pthread_mutex_lock (&lock);
		val = reading_value_of_device();
		printf("The current value of the device is %d\n", val);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	pthread_exit(NULL);
}

// this function returns the value read inside the device
int reading_value_of_device (void) {
	int fd; // file descriptor needed to read from the device
	int val; // value read from the device
	char buffer [BUFLEN + 1];
	
	fd = open (DEVICE_NAME, O_RDONLY);
	
	// error check
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		exit(EXIT_FAILURE);			
	}
	
	read(fd, buffer, BUFLEN);
	
	val = atoi(buffer);
	
	close (fd); // close the file
	
	return val;
}

// routine for the updater
void * updater (void * arg) 
{
	int coin; // random value used to decide whether to increment or decrement the value
	int current; // current value of the device	
	
	while (1)
	{
		// reserve the access to the device for the whole duration of the operations
		pthread_mutex_lock (&lock);
		current = reading_value_of_device();
		// set the value of the increment depending on the return value of coin_toss
		if (coin_toss())
		{
			coin = 1;
		}	else
		{
			coin = -1;
		}
	
		// update the value
		current += coin;
		
		// write on the device the updated value
		writing_on_device(current);

		// free the access to the device
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	
	pthread_exit(NULL);
}

// generates a pseudorandom value by computing the remainder of a random number
int coin_toss (void)
{
	int random;
	// generate a random number and see if it's even or odd
	random = (int) rand();
	return random % 2; // return the remainder
}

// function used to write on the device the new value
void writing_on_device (int new) {
	int fd;
	char buffer[BUFLEN];
	
	/* the following set of instructions is used to clean the current value of the device */
	strcpy (buffer, "                      ");
	fd = open (DEVICE_NAME, O_WRONLY);
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		exit(EXIT_FAILURE);
	}
	write(fd, buffer, strlen(buffer));
	close (fd);		
	/* cleaned */
	
	// now the value of the device is updated
	fd = open (DEVICE_NAME, O_WRONLY);
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		exit(EXIT_FAILURE);
	}
	buffer[0] = '\0';
	sprintf(buffer, "%d", new);
	
	write(fd, buffer, strlen(buffer));

	close (fd);		
}
