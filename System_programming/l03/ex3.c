/**
	Write a program that creates 2 threads: 
	- the first reads data from a file whose name is
	 	given as a command line parameter and sends it
	 	to the second thread
	- the second one receives data from the first thread and
		writes on the second file passed on the command line
	
	
	sysprog03
	
	Riccardo Cappuzzo
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> //needed for file manipulation

#define BUF_LEN 512 // size of the common buffer

void * reader (void * arg);
void * writer (void * arg);

struct thread_data {
	int thread_id; 
	int fd; // file descriptor
}; 

// I need 2 locks arranged in a producer/consumer fashion
pthread_mutex_t lock1; 
pthread_mutex_t lock2;

char buffer[BUF_LEN+1]; // the size+1 is needed to account for the \0 character

int 
main (int argc, char *argv[])
{
	pthread_t tid1, tid2; 	
	int fd1, fd2;
	
	struct thread_data *arg_reader;
	struct thread_data *arg_writer;

	// explicit allocation of the arg structs
	arg_reader = (struct thread_data *) malloc (sizeof(struct thread_data));
	arg_writer = (struct thread_data *) malloc (sizeof(struct thread_data));
	
	// initialization of the mutex locks
	pthread_mutex_init (&lock1, NULL);
	pthread_mutex_init (&lock2, NULL);
	
	// error checks and initialization of file descriptors
	if (argc != 3)
	{
		fprintf (stderr, "Wrong number of arguments\n");
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	fd1 = open(argv[1], O_RDONLY); // open the input file
	if (fd1 == -1) {
		fprintf (stderr, "Input file could not be opened\n");
		exit(1);
	}
	
	fd2 = open(argv[2], O_CREAT | O_WRONLY, 0622); // create the output file
	
	if (fd2 == -1) {
		fprintf (stderr, "Output file could not be created\n");
		exit(1);
	}
	
	// I assign the values of the arguments
	arg_reader->thread_id = 0; // reader
	arg_reader->fd = fd1;
	
	arg_writer->thread_id = 1; // writer
	arg_writer->fd = fd2;
	
	pthread_create (&tid1, NULL, reader, (void *) arg_reader);
	pthread_create (&tid2, NULL, writer, (void *) arg_writer);	
	
	// joining the threads at the end of the procedure
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	// closing file descriptors
	close(fd1);
	close(fd2);
	
	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	
	
	return 0;
}

void * reader (void * arg)
{
	int fd, count_input;
	char int_buffer[BUF_LEN]; 
	struct thread_data *args;
	
	args = (struct thread_data *) arg;
	
	fd = args->fd;
	while((count_input = read(fd, int_buffer, BUF_LEN)) > 0)
	{
		int_buffer[count_input] = '\0'; // explicitly setting the last character of the string
		pthread_mutex_lock (&lock1);
		strcpy (buffer, int_buffer);
		pthread_mutex_unlock (&lock2);
	} 
	// explicitly terminating the reading of the file
	pthread_mutex_lock (&lock1); 
	buffer[0] = '\0';
	pthread_mutex_unlock (&lock2);

	pthread_exit(NULL);
}

void * writer (void * arg)
{
	struct thread_data *args;
	int len = 1;
	int fd;
	
	args = (struct thread_data *) arg;
	fd = args->fd;
	
	while (len > 0) // this will read as long as something is present in the shared buffer
	{
		pthread_mutex_lock (&lock2);
		len = strlen(buffer);
		write(fd, buffer, len);
		pthread_mutex_unlock (&lock1);
	}
	
	pthread_exit(NULL);
}

