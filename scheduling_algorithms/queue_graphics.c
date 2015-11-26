#include "queue_graphics.h"

void print_single_queue(int * queue, int queue_length)
{
    int i;

    for (i = 0; i < MAX_LENGTH - queue_length; i++)
    {
        printf("-");
    }
    for (i = 0; i < queue_length; i++)
    {
        if (queue[i] == 1)
        {
            printf("*");
        } else {
            printf("-");
        }
    }
    printf("\n");
}
