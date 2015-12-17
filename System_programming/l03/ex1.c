/**
   Write a C process that creates a large number of processes/threads.
   Find the maximum number of process and threads that it is possible to create.
   Compute the time needed to create and destroy processes and threads.

   sysprog03

   Riccardo Cappuzzo

 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define LARGE_NUMBER 100000*3

void * runner (void * arg){
  int *val;
  val = (int *) arg;
  pthread_exit(NULL);
}

int main (int argc, char **argv)
{
  int i, status;
  pid_t pids[LARGE_NUMBER];
  pthread_t tids[LARGE_NUMBER];
  char option;

  if (argc != 2){
    printf("Usage: %s <option>\nOption: P for Processes, T for Threads\n", argv[0]);
    exit(1);
  }

  option = argv[1][0];
  
  switch (option){
  case 'P': // generate processes
    printf("Processes\n");
    for (i = 0; i < LARGE_NUMBER; i++){
      pids[i] = fork();
      if (pids[i] == 0)
      {// child process
		exit(0);
      } else {
	// parent process
		wait(&status);
      }
    }
    printf("Created %d processes\n", i);
    break;
  case 'T': // generate threads
    printf("Threads\n");
    for (i = 0; i < LARGE_NUMBER; i++){
      if (pthread_create(&tids[i], NULL, runner, (void *) &i)){
	printf("ERROR in pthread_create()\n");
	exit(-1);
      }
      pthread_join(tids[i], NULL);
    }    
    printf("Created %d threads\n", i);
    break;
  default:
    printf("Wrong letter\n");
    break;
  }

  return 0;
}
