/**
    Write a simple producer-consumer program, in which the queue between
    the two processes (father and son, or two brothers) is at most of 4 tokens, each token
    being a character. Use semaphores to protect the producer-consumer operations.

    sysprog2

    Riccardo Cappuzzo

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


void semaphore_init (int *sw);
void semaphore_signal (int *sw);
void semaphore_wait (int *sw);

int main()
{
    pid_t pid;
    int sem[2];

    semaphore_init(sem);
    pid = fork();

    if (pid == 0)
    {
        // child process
        printf("Starting child\n");
        semaphore_wait(sem);
        printf("wait1\n");
        semaphore_wait(sem);
        printf("wait2\n");
        semaphore_wait(sem);
        printf("wait3\n");
        semaphore_wait(sem);
        printf("wait4\n");
        printf("Child completed wait\n");
    } else
    {
        // parent process
        printf("Starting parent\n");
        semaphore_signal(sem);
        printf("signal1\n");
        semaphore_signal(sem);
        printf("signal2\n");
        semaphore_signal(sem);
        printf("signal3\n");
        semaphore_signal(sem);
        printf("signal4\n");
        printf("Parent completed signal\n");

    }

    return 0;
}

void semaphore_init (int *sw)
{
    if (pipe(sw) == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void semaphore_wait (int *sw)
{
    char buffer;
    if (read(sw[0], &buffer, 1) != 1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void semaphore_signal (int *sw)
{
    if (write(sw[1], "x", 1) != 1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
