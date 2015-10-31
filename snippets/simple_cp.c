/*
    Write a program able to copy data contained in a file whose name is a
    command line parameter in a second file whose name is passed as a second parameter

    Author: Riccardo Cappuzzo

    2015/10/31
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUF_LEN 1024

int main(int argc, char ** argv)
{
    int finn, fout;
    char buffer[BUF_LEN];
    int count = 0;

    if (argc != 3) {
        fprintf(stderr, "Wrong number of arguments.\n");
        exit(1);
    }

    finn = open (argv[1], O_RDONLY);
    fout = open (argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (finn == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    if (fout == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    while ( (count = read(finn, buffer, BUF_LEN)) > 0 ) {
        if ((write(fout, buffer, count)) == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        }
    }

    close(finn);
    close(fout);

    return 0;
}
