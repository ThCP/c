#include <stdio.h>
#include <stdlib.h>
#include "queue_graphics.h"

int main()
{
    int i;
    int queue1[] = {0,0,0,0,1,1,1,1,1,1,1};
    int queue2[] = {0,0,1,0,1,0,1,0,1,0,1};
    int queue3[] = {0,0,0,1,1,1,0,0,0,0,0};

    print_single_queue(queue1, 11);
    print_single_queue(queue2, 11);
    print_single_queue(queue3, 11);


    return 0;
}
