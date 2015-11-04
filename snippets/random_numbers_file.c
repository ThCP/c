/**
	This program generates a txt file which contains a random number of 
	values randomly chosen in a range defined by the constant MAX_RAND
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAX_RAND  100
#define BUF_LEN 100

int main(int argc, char ** argv)
{

    int fout;
    int list_length;
    int rand_value;
    int i, count_write;
    char buffer[BUF_LEN];


    fout = open("random.txt", O_WRONLY | O_SYNC | O_CREAT, S_IWUSR | S_IWGRP | S_IWOTH | S_IRUSR | S_IRGRP | S_IROTH); // I should use creat here

    if (fout == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    list_length = rand() % MAX_RAND; // prova funzione random, setta il seme casuale

    for (i = 0; i < list_length; i++) {
        rand_value = rand() % MAX_RAND;
        sprintf(buffer, "%d ", rand_value);
        count_write = write(fout, buffer, strlen(buffer));
        if (count_write == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    close(fout);

    return 0;
}

