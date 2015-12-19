/**
   Write a counting program with 2 threads. 
   The first thread should loop incrementing a counter as fast as it can.
   The second thread should occasionally read the counter value and print it.

	This is a modified version of ex2.c with a mutex lock 
	protecting the counter.
	
   sysprog03

   Riccardo Cappuzzo
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define SLEEP_FOR 1 // checks the value of the counter ever SLEEP_FOR seconds
#define LOOP_FOR 10 // keeps looping for LOOP_FOR times, so that the program does not keep on going forever

long long counter = 0;
int loop = 1;

pthread_mutex_t lock;

void * runner (void * arg){
  
  while (loop) { // end when loop = 0
      pthread_mutex_lock(&lock); // protect the increment
    counter++;
        pthread_mutex_unlock(&lock);
  }

  pthread_exit(NULL);
}

int main (int argc, char **argv)
{
  pthread_t tid;
  int i;
	long long c;
	pthread_mutex_init (&lock, NULL); // initialization of mutex

  if (pthread_create(&tid, NULL, runner, NULL)){
    printf("Error in pthread_create()\n");
    exit(1);
  }
	//check the value of the counter
  for (i = 0; i < LOOP_FOR; i++) {
    sleep(SLEEP_FOR);
    pthread_mutex_lock(&lock); // protect the print operation
    c = counter;
    pthread_mutex_unlock(&lock);
    printf("value of counter = %lld\n", c);
    
  }

  loop = 0; // end the loop so that the runner can complete

  pthread_join(tid, NULL); 

  return 0;
}
