#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *runner1 (void *arg);
void *runner2 (void *arg);
void *runner4 (void *arg);
void *runner3 (void *arg);

void child1(void);
void child2(void);

int shared_variable = 1;

int 
main (int argc, char *argv[])
{
	pid_t pid1, pid2;
	
	pid1 = fork();
	if (pid1 == -1) {
		fprintf (stderr, "error in fork\n");
		exit(1);
	}
	
	else if (pid1 == 0)
	{
		//child process
		printf("I am the first child, my pid is %d, my parent is %d\n", getpid(), getppid());
		child1();
	} else
	{
		//parent process
		pid2 = fork();
		if (pid2 == -1)
		{
			fprintf (stderr, "error in fork\n");
			exit(1);
		}
		
		else if (pid2 == 0)
		{
			//child process
			printf("I am the second child, my pid is %d, my parent is %d\n", getpid(), getppid());
			child2();
		} else
		{
			//parent process
			printf("I am the parent process.\n");	
			wait(NULL);
			wait(NULL);
			printf("Process is over\n");
		}
	}
	
	return 0;
}

void child1(void)
{
	pthread_t tid1, tid2;	
	printf("Child1: The shared variable is now %d\n", shared_variable);
	shared_variable = 10;
	printf("Child1: The shared variable is now %d\n", shared_variable);
	sleep(5);
	pthread_create(&tid1, NULL, runner1, (void*) &shared_variable);
	pthread_create(&tid2, NULL, runner2, (void*) &shared_variable);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	sleep(5);
	printf("End of child1\n");
}


void child2(void)
{
	pthread_t tid1, tid2;
	printf("Child2: The shared variable is now %d\n", shared_variable);
	shared_variable = 20;
	printf("Child2: The shared variable is now %d\n", shared_variable);
	sleep(1);
	pthread_create(&tid1, NULL, runner3, (void*) &shared_variable);
	pthread_create(&tid2, NULL, runner4, (void*) &shared_variable);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	sleep(2);
	printf("Now switching to exec.\n");
	
	execlp("echo", "echo", "test", (char *) 0);	
	printf("End of child 2\n");
}

void *runner1 (void *arg)
{
	int *var = (int *)arg;
	printf("inside child 1 - thread1: The shared variable is now %d\n", *var);
	shared_variable = 100;
	sleep(1);
	printf("inside child 1 - thread1: The shared variable is now %d\n", shared_variable);
}

void *runner2 (void *arg)
{
	int *var = (int *)arg;
	printf("inside child 1 - thread2: The shared variable is now %d\n", shared_variable);
	shared_variable = shared_variable*45;
	sleep(1);
	printf("inside child 1 - thread2: The shared variable is now %d\n", shared_variable);
}

void *runner3 (void *arg)
{
	int *var = (int *)arg;
	printf("inside child 2 - thread1: The shared variable is now %d\n", *var);
	shared_variable = 100;
	sleep(1);
	printf("inside child 2 - thread1: The shared variable is now %d\n", shared_variable);
}

void *runner4 (void *arg)
{
	int *var = (int *)arg;
	printf("inside child 2 - thread2: The shared variable is now %d\n", shared_variable);
	shared_variable = shared_variable*22;
	sleep(1);
	printf("inside child 2 - thread2: The shared variable is now %d\n", shared_variable);
}


