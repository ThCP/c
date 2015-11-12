#include "network_algorithms.h"

Graph generate_network (char *filename)
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

    fclose(finn);
    return G;

}


int ** generate_flows (char * filename)
{
    FILE * finn;
    finn = fopen(filename, "r");
    int n;
    int ** flows;

    if (finn == NULL)
    {
        fprintf(stderr, "Error in opening file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(finn, "%d", &n);



}


flow * my_flow_alloc ( int n )
{



}
