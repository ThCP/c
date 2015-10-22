/*

Write a program that allows the storage of a set of coordinates in the Cartesian
coordinate system. Define in the program a data structure containing two fields as
follows:
struct coordinate{
int x;
int y;
};
The program shall acquire by the keyboard the coordinates x and y of 4 points,
corresponding to the points of a path and manipulates the received data on the basis of
a parameter received from the command line:
• Parameter “–m” : computes and prints on the screen the length of the path
composed by the 4 segments.
• Parameter “–a” : computes and prints on the screen the minimum length between
the given coordinates.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _COORDINATE{
int x;
int y;
} typedef coordinate;

int main(int argc, char *argv[])
{

    int i;
    float modulus, totalPath, minimumDistance;
    coordinate CartesianPlane[4];

    if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments\n");
    abort();

    }//end check number of arguments

    if (argv[1][0] != '-'){

            fprintf(stderr, "Wrong argument syntax.\n");
            abort();

    }

    else if (argv[1][0] == '-'){

        if ((argv[1][1] != 'l')&&(argv[1][1] != 'm')){

            fprintf(stderr, "Wrong argument syntax.\n");
            abort();

        }
    }//end if check argument

    for (i = 0; i < 4; i++){

        fprintf(stdout, "Insert the x coordinate of the point number %d ", i+1);
        fscanf(stdin, "%d", &CartesianPlane[i].x);

        fprintf(stdout, "Insert the y coordinate of the point number %d ", i+1);
        fscanf(stdin, "%d", &CartesianPlane[i].y);

    }

    switch(argv[1][1]){

        case 'm':

        totalPath = 0;

        for (i = 0; i < 4; i++){

            modulus = sqrt(CartesianPlane[i].x*CartesianPlane[i].x + CartesianPlane[i].y*CartesianPlane[i].y);
            totalPath+=modulus;

        }

        fprintf(stdout, "The total path is %g\n", totalPath);

        break;



        case 'a':

        minimumDistance = sqrt(CartesianPlane[0].x*CartesianPlane[0].x + CartesianPlane[0].y*CartesianPlane[0].y);
        for (i = 1; i < 4; i++){

            modulus = sqrt(CartesianPlane[i].x*CartesianPlane[i].x + CartesianPlane[i].y*CartesianPlane[i].y);
            if (minimumDistance > modulus) minimumDistance = modulus;

        }//end for

        fprintf(stdout, "The minimum distance is %g\n", minimumDistance);

        break;

    }//end switch

    return 0;
}
