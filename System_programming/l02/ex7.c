/**
	Write a program that creates a pipe and after the fork() uses the pipe to
	send a large file from one process to the other during the execution.

	Riccardo Cappuzzo
	
	s231643

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define BUF_LEN 512


int file_pipe[2];

int main(int argc, char ** argv)
{
    int count_pipe, count_large_file;
    int finn, fout;
    pid_t pid1;
    char buffer[BUF_LEN+1];

	if (argc != 2)
	{
		fprintf(stderr, "Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}

    if (pipe(file_pipe) == 0) {

       
		
        pid1 = fork();

        if (pid1 == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (pid1 == 0) {
            // child process
            fout = open("out", O_WRONLY | O_CREAT, S_IWUSR | S_IWGRP | S_IRUSR);
            close(file_pipe[1]); // child reads only on pipe
            while ((count_pipe = read(file_pipe[0], buffer, BUF_LEN)) > 0) { // read from pipe the buffer
                if ((count_large_file = write(fout, buffer, count_pipe)) == -1) { // write the content of the buffer on the output file
                    printf("error %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
            }
            close(fout); // writing operation completed, closing output file
            exit(EXIT_SUCCESS);
        } else {
            // parent process
 			finn = open(argv[1], O_RDONLY); // open the input file passed on the command line

			if (finn == -1) { // check if finn exists
			    fprintf(stderr, "%s\n", strerror(errno));
        	    exit(EXIT_FAILURE);
			}
 
            close (file_pipe[0]); // parent writes only on pipe

            while ((count_large_file = read(finn, buffer, BUF_LEN-1)) > 0) {
                count_pipe = write(file_pipe[1], buffer, count_large_file);
            }
            close(finn);
            exit(EXIT_SUCCESS);
        }

    }

    return 0;
}
