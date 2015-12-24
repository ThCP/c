/* 
	This program realizes the following precedence graph:
			A
		+---+----+
		B	|	 D
		|	C	 |
		| +-+-+  |
		| |	  |	 |
		| E	  F	 |
		| |	  |	 |
		| +-+-+  |
		| 	G	 H
		|  	|	 |
		+---+----+
			|
			I
	
	Multiple processes are created and synchronization is achieved by means of pipes.
	
	Author: Riccardo Cappuzzo
	2015-08-20
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * tf1(void *ptr);
void * tf2 (void *ptr);
void * tf3 (void *ptr);

int main () {
	pthread_t t1,t2,t3;
	char *junk = "x";
	void * exitStatus;
	
	
	pthread_create (&t1, NULL, tf1, (void *) junk);
	pthread_create (&t2, NULL, tf2, (void *) junk);
	pthread_create (&t3, NULL, tf1, (void *) junk);
	
	pthread_join(t1, &exitStatus); 
	pthread_join(t2, &exitStatus); 
	pthread_join(t3, &exitStatus); 
	
	printf("joined threads B, G, D\n");

	return 0;
	
}

void * tf1(void *ptr) {
	printf ("inside thread function 1, thread A/B\n");
	
	return;	
}
void * tf2 (void *ptr){
	pthread_t t1,t2;
	char *junk = "x";
	void * exitStatus;
	
	printf ("inside thread function 2, thread C\n");
	
	pthread_create (&t1, NULL, tf3, (void *) junk);
	pthread_create (&t2, NULL, tf3, (void *) junk);
	
	pthread_join(t1, &exitStatus);
	pthread_join(t2, &exitStatus);
	
	printf("joined threads E and F\n");
	
	return;
}


void * tf3(void *ptr) {
	printf ("inside thread function 3, thread E/F\n");
	
	return;	
}

