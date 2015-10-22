#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _COORDINATE{
int x;
int y;
} typedef coordinate;



int main(int argc, char *argv[])
{
    int i, j;
    float modulus, modSquare, totalPath, minimumDistance;
    coordinate CartesianPlane[4];
    modulus = 0;

    if (argc != 10){

        fprintf(stderr, "Wrong number of arguments.\n");
        abort();

    }//end if

     if (argv[1][0] != '-'){

            fprintf(stderr, "Wrong argument syntax.\n");
            abort();

    }

    else if (argv[1][0] == '-'){

        if ((argv[1][1] != 'a')&&(argv[1][1] != 'm')){

            fprintf(stderr, "Wrong argument syntax.\n");
            abort();

        }
    }//end if check argument
    j = 0;
    for (i = 2; i < argc; i+=2){

        sscanf(argv[i], "%d", &CartesianPlane[j].x );
        j++;

    }
    j = 0;
    for (i = 3; i < argc; i+=2){

        sscanf(argv[i], "%d,", &CartesianPlane[j].y );
        j++;

    }

        switch(argv[1][1]){

        case 'm':

        totalPath = 0;
        modulus = 0;
        modSquare = 0;

        for (i = 0; i < 4; i++){
            modSquare = (float)(CartesianPlane[i].y*CartesianPlane[i].y + CartesianPlane[i].x*CartesianPlane[i].x);
            modulus = sqrt(modSquare);
            totalPath += modulus;

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
