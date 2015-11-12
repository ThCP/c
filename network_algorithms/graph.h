#include <stdlib.h>
#include <stdio.h>

typedef struct {
            int v;
            int w;
            double weight;
            int satisfied;
            double occupation;
    }   Edge;

Edge EDGE (int, int, double);

typedef struct graph * Graph;
Graph GRAPHinit (int); // integer number of vertices
void GRAPHinsertE (Graph, Edge);
void GRAPHremoveE (Graph, Edge);
int GRAPHedges (Edge [], Graph G);
Graph GRAPHcopy (Graph);
void GRAPHdestroy (Graph);
void GRAPHshow (Graph);
