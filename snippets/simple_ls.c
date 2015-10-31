#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char ** argv)
{
    DIR * dp;
    struct dirent *link;

    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        exit(1);
    }

    dp = opendir(argv[1]);

    if (dp == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));

        exit(1);
    }

    while ((link = readdir(dp)) != 0) {
        printf("%s\n", link->d_name);
    }

    closedir(dp);

    return 0;
}
