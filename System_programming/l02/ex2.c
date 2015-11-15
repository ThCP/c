/**
	ex2
	
	Write a simplified version of the ls command receiving as a command line
	parameter the name of a directory and that visualizes the names of all the files contained
	in this directory

	sysprog 2
	
	Riccardo Cappuzzo
	s231643

*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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
        fprintf(stderr, "Error in opening the folder\n");
        exit(1);
    }

    while ((link = readdir(dp)) != 0) {
        printf("%s\n", link->d_name);
    }

    return 0;
}
