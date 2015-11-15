#include <stdio.h>
#include <stdlib.h>
#include "network_algorithms.h"

int main(int argc, char ** argv)
{
    Graph G = NULL;

//    if (argc != 2)
//    {
//        fprintf(stderr, "Wrong number of arguments.\n");
//        exit(EXIT_FAILURE);
//    }

    G = generate_network("in");
//    G = read_file(argv[1]);

    GRAPHshow(G);

    return 0;
}

