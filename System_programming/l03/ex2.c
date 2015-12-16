/**
   Write a counting program with 2 threads. 
   The first thread should loop incrementing a counter as fast as it can.
   The second thread should occasionally read the counter value and print it.

   sysprog03

   Riccardo Cappuzzo
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define SLEEP_FOR 1 // checks the value of the counter ever SLEEP_FOR seconds
#define LOOP_FOR 10 // keeps looping for LOOP_FOR times, so that the program does not keep on going forever

long long counter = 0;
int loop = 1;

void * runner (void * arg){
  
  while (loop) {
    counter++;
  }

  pthread_exit(NULL);
}

int main (int argc, char **argv)
{
  pthread_t tid;
  int i;

  if (pthread_create(&tid, NULL, runner, NULL)){
    printf("Error in pthread_create()\n");
    exit(1);
  }

  for (i = 0; i < LOOP_FOR; i++) {
    sleep(SLEEP_FOR);
    printf("value of counter = %lld\n", counter);
  }

  loop = 0;

  pthread_join(tid, NULL);

  return 0;
}
