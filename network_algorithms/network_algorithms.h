#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct {
    char name [128+1];
    int satisfied;
    int capacity;
    int * path;
    struct flow * next;
} flow;

Graph generate_network (char *filename);
int ** generate_flows (char * filename);
