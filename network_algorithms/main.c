#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph read_file (char *);
void print_adj_matrix ( Graph );

int main(int argc, char ** argv)
{
    Graph G = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    G = read_file(argv[1]);

    GRAPHshow(G);

    return 0;
}

Graph read_file (char *filename)
{
    FILE *finn;
    int n;
    int v, w;
    double weight;
    Edge e;
    Graph G = malloc(sizeof(Graph));

    finn = fopen(filename, "r");
    if (finn == NULL)
    {
        fprintf(stderr, "Error in opening file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf (finn, "%d", &n);

    G = GRAPHinit(n);

    while ( (fscanf(finn, "%d-%d %lf", &v, &w, &weight)) > 0 )
    {
        e = EDGE(v, w, weight);
        GRAPHinsertE(G, e);
    }

    return G;

}

