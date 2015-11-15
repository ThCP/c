/**
    Exercise 9
    Write a C program that performs the following operations:
        Creates a child process that generates a file called random.txt containing a list of
        random numbers separated by the space character. Let the length of this list be a
        random value too.
    When the file is created the program must instantiate three sub-processes:
        - The first process must execute the linux command wc –m to print on the
        screen the number of bytes of the file.
        - The second process must execute the linux command wc –w to count the
        number of words in the file
        - The third process must execute a custom program designed to compute the
        average of all generated numbers.
        - The main process terminates when all three children terminate.

    Riccardo Cappuzzo
    
    s231643
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_RAND  100 // I set a max value so to avoid creating a file too big to handle
#define MAX_VALUE 10000 // max value the random values can take 
#define BUF_LEN 10 

void generate_file(void);

int main(int argc, char ** argv)
{
    pid_t pid1, pid2, pid3;
    int status;

    pid1 = fork();

    if (pid1 == 0) {
        //child process
        generate_file();
        printf("File created.\n");
        exit(EXIT_SUCCESS);
    }  else {
        //parent process
        waitpid( pid1, &status, 0);
        pid1 = fork();
        if (pid1 == 0) {
            //child process
            execlp("wc", "wc", "-m", "random.txt", (char * ) 0);
        } else {
        	//parent process
            pid2 = fork();
            if (pid2 == 0) {
                //child process
                execlp("wc", "wc", "-w", "random.txt", (char *) 0);
            } else {
                //parent process
                pid3 = fork();
                if (pid3 == 0) {
                    //child process
                    execl("./average", "average", "random.txt", (char *) 0); //use the "average" program 
                }   else {
//                    parent process
                    waitpid(pid1, &status, 0);
                    printf("Child %d terminated with status %d\n", pid1, status);
                    waitpid(pid2, &status, 0);
                    printf("Child %d terminated with status %d\n", pid2, status);
                    waitpid(pid3, &status, 0);
                    printf("Child %d terminated with status %d\n", pid3, status);
                }
            }
        }
    }
    return 0;
}

void generate_file(void) {
    int fout;
    int list_length;
    int rand_value;
    int i, count_write;
    char buffer[BUF_LEN];

    fout = open("random.txt", O_WRONLY | O_SYNC | O_CREAT, S_IWUSR | S_IWGRP | S_IWOTH \
                                | S_IRUSR | S_IRGRP | S_IROTH); 

    if (fout == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    list_length = rand() % MAX_RAND;

    for (i = 0; i < list_length; i++) {
        rand_value = rand() % MAX_VALUE;
        sprintf(buffer, "%d ", rand_value);
        count_write = write(fout, buffer, strlen(buffer));
        if (count_write == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    close(fout);

}
