#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define BUF_LEN 512

int file_pipe[2];

int main()
{
    int count_pipe, count_large_file;
    int finn, fout;
    pid_t pid1;
    char buffer[BUF_LEN+1];

    if (pipe(file_pipe) == 0) {

        finn = open("prova", O_RDONLY);

        pid1 = fork();

        if (pid1 == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (pid1 == 0) {
            // child process
            fout = open("out", O_WRONLY | O_CREAT, S_IWUSR | S_IWGRP | S_IRUSR);
            close(file_pipe[1]); // child reads only
            while ((count_pipe = read(file_pipe[0], buffer, BUF_LEN)) > 0) {

                if ((count_large_file = write(fout, buffer, count_pipe)) == -1) {
                    printf("error %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
            }
            close(fout);
            exit(EXIT_SUCCESS);
        } else {
            // parent process
            close (file_pipe[0]); // parent writes only

            while ((count_large_file = read(finn, buffer, BUF_LEN-1)) > 0) {
//                printf("b %s\n", buffer);
//
                count_pipe = write(file_pipe[1], buffer, count_large_file);
//                printf("b %d\n", (int)strlen(buffer));
//                printf("c %d\n", count_large_file);
            }
            close(finn);
            exit(EXIT_SUCCESS);
        }

    }

    return 0;
}
