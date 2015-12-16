#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define BUF_LEN 1024

void * reader (void * arg);
void * writer (void * arg);

pthread_mutex_t lock; // I need a mutex in order to protect the reading/writing operations from concurrent access

struct thread_data {
	int thread_id;
	int fd;
};

struct thread_data arg_reader;
struct thread_data arg_writer;

char buffer[BUF_LEN];

int 
main (int argc, char *argv[])
{
	pthread_t tid1, tid2; 	
	int fd1, fd2;
	
	if (argc != 3)
	{
		fprintf (stderr, "Wrong number of arguments\n");
		exit(1);
	}
	
	fd1 = open(argv[1], O_RDONLY); // open the input file
	if (fd1 == -1) {
		fprintf (stderr, "Input file could not be opened\n");
		exit(1);
	}
	
	fd2 = creat(argv[2], 0622); // create the output file
	
	if (fd2 == -1) {
		fprintf (stderr, "Output file could not be created\n");
		exit(1);
	}
	
	// I assign the values of the arguments
	arg_reader.thread_id = 0; // reader
	arg_reader.fd = fd1;
	
	arg_writer.thread_id = 1; // writer
	arg_writer.fd = fd2;
	
	pthread_create (&tid1, NULL, reader, (void *) arg_reader);
	pthread_create (&tid2, NULL, writer, (void *) arg_writer);	
	
	return 0;
}

void * reader (void * arg) {
	

void * writer (void * arg);



void Producer(void * arg)
{
    int val, i = 0;
    int *fd;
    fd = (int * ) arg;
    int count_input;
    char int_buffer[BUF_LEN];
    
    while((count_input = read(fd, int_buffer, BUF_LEN)) > 0)
    {
 		//produce(); // fill the produce function with the appropriate commands
        sem_wait(empty);
        enqueue(int_buffer); // enqueue function
        sem_post(full);
    }
}

void Consumer()
{
    int val;
    int i = 0;
    while(i<MAX_REP) // in this way the program does not run forever
    {
        sem_wait(full);
        dequeue();  // dequeue function
        sem_post(empty);
        consume(); // consume function
        i++;
    }
}

// this should contain the functions that should be performed by the producer
void produce()
{
    printf("Producing\n");
}	

void enqueue()
{
	printf("Enqueue\n");
}


// this should contain the functions that should be performed by the consumer
void consume()
{
    printf("Consuming\n");
}	

void dequeue()
{
	printf("Dequeue\n");
}
