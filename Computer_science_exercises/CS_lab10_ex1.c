/*

Write a C program that, given three parameters from the command line val1, val2
and ch, corresponding to 2 integers numbers (val1 and val2) and 1 character (ch),
performs the following operations, according to the value of ch, and displays on
the screen the corresponding result:
• ch = a : val1 + val2
• ch = b : val1 – val2
• ch = c : val1 * val2
• ch = d : val1 / val2 , if val2 is different from 0, otherwise print on the
screen an error message.

LAIB 10 exercise 1, 31-05-2013

*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int val1, val2;
    char ch;

    if (argc != 4){

        fprintf(stderr, "Wrong number of arguments.\n");
        abort();

    }   //end check number of arguments

    sscanf(argv[1], "%c", &ch);
    sscanf(argv[2], "%d", &val1);
    sscanf(argv[3], "%d", &val2);

    switch (ch){

        case 'a':
                printf("%d + %d = %d\n", val1, val2, val1+val2);
                break;
        case 'b':
                printf("%d - %d = %d\n", val1, val2, val1-val2);
                break;
        case 'c':
                printf("%d * %d = %d\n", val1, val2, val1*val2);
                break;
        case 'd':

                if (val2 != 0){
                printf("%d / %d = %d\n", val1, val2, val1/val2);
                break;
                }//end if division
                else {
                fprintf(stderr, "val2 cannot be 0\n");
                abort();

                } //end else division

    }//end swich

    return 0;
}
