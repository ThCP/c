#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

double **MATRIXinit (int r, int c, int val);

struct graph {  int V; // number of vertices
                int E; // number of edges
                double ** adj; // adjacency matrix, double because of possible double weights
                };

Graph GRAPHinit(int V)
{
    Graph G = malloc( sizeof *G );
    if (G == NULL)
    {
        fprintf(stderr, "Error in allocation of Graph pointer.\n");
        exit(EXIT_FAILURE);
    }

    G->V = V;
    G->E = 0;
    G->adj = MATRIXinit(V, V, 0); // create a VxV matrix initialized to 0

    return G;
}

void GRAPHinsertE (Graph G, Edge e)
{
    int v = e.v-1;
    int w = e.w-1;

    if (G->adj[v][w] == 0) G->E++;

    G->adj[v][w] = e.weight;
    G->adj[w][v] = e.weight;
}


void GRAPHremoveE (Graph G, Edge e)
{
    int v = e.v-1;
    int w = e.w-1;

    if (G->adj[v][w] != 0) G->E--;

    G->adj[v][w] = 0;
    G->adj[w][v] = 0;
}

int GRAPHedges (Edge a[], Graph G)
{
    int v, w, E = 0;
    for (v = 0; v < G->V; v++)
    {
        for (w = v+1; w < G->V; w++)
        {
            if (G->adj[v][w] != 0)
                a[E++] = EDGE(v, w, G->adj[v][w]);
        }
    }
    return E;
}
Graph GRAPHcopy (Graph);
void GRAPHdestroy (Graph);

Edge EDGE (int v, int w, double weight)
{
    Edge E;

    E.occupation = 0.0;
    E.satisfied = 0;
    E.v = v;
    E.w = w;
    E.weight = weight;

    return E;
}


double **MATRIXinit (int r, int c, int val)
{
    double ** nP = NULL;
    int i;

    nP = ( double ** ) malloc(r * sizeof ( double * ));

    if (nP == NULL)
    {
        fprintf(stderr, "Error in allocation of matrix\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < c; i++)
    {
        nP[i] =  (double * ) malloc( c * sizeof ( double ));
        if (nP[i] == NULL)
        {
            fprintf(stderr, "Error in allocation of matrix\n");
            exit(EXIT_FAILURE);
        }
    }

    return nP;
}

void GRAPHshow (Graph G)
{
    int i, j;
    int V;
    V = G->V;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++);
        {
            printf("%lf ", G->adj[i][j]);
        }
        printf("\n");
    }

}
