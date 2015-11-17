#include <stdio.h>
#include <stdlib.h>
#include "semaphore.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_QUEUE 4
#define MAX_REP 5 // program stops after 5 iterations, it would run forever otherwise

sem_t *empty, *full;

void Producer();
void Consumer();

int main()
{
    pid_t pid;

    /*
    In order to use the posix semaphores I need to allocate memory shared between the producer and the consumer.
    I am using two named semaphores instead.
    */
    empty = sem_open("empty", O_CREAT, S_IRUSR | S_IWUSR, MAX_QUEUE); // the empty semaphore is init. with the max value
    full = sem_open("full", O_CREAT, S_IRUSR | S_IWUSR, 0); // the full semaphore is init. with value 0

    pid = fork(); // create the child

    if (pid == -1) { // fork error check
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        //child process
        sleep(3);
        printf("Child process\n");
        Consumer();
    } else {
        //parent process
        printf("Parent process\n");
        Producer();
    }

    return 0;
}

void Producer()
{
    int val, i = 0;
    while(i<MAX_REP) // in this way the program does not run forever
    {
        printf("Producing\n");
        sem_wait(empty);
        printf("Enqueuing\n");
        sem_post(full);
        i++;
    }
}

void Consumer()
{
    int val;
    int i = 0;
    while(i<MAX_REP) // in this way the program does not run forever
    {
        sem_wait(full);
        printf("Dequeuing\n");
        sem_post(empty);
        printf("Consuming\n");
        i++;
    }
}
