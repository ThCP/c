/*
Si scriva un programma che legga da un file (il cui nome è ricevuto come
primo parametro sulla linea di comando) alcune informazioni ferroviarie.
Per ciascuna linea, il file contiene le seguenti informazioni (ciascuno dei
campi non superi i 20 caratteri di lunghezza e sia privo di spazi)
<stazione_partenza> <ora_partenza> <stazione_arrivo> <ora_arrivo>
Il programma può eventualmente ricevere come ulteriore parametro da
linea di comando il nome di una città; in tale caso, il programma calcoli e
stampi il numero di treni in arrivo ed il numero di treni in partenza da tale
città (se inclusa nell’elenco).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

struct _HOUR {

    int mm;
    int hh;
    int ss;

} typedef Hour;

struct _TRAIN_TABLE {

    char departure[20+1];
    char arrival[20+1];

    Hour hour_departure;
    Hour hour_arrival;

} typedef Table;

/*prototypes*/
int find_city(char city[20], int *start, int *arrive, int tot_rows, Table trains[]);




int main(int argc, char *argv[])
{
    FILE *f;
    Table Trains[MAX_SIZE];
    int i, result, starting, arriving;
    char whole_line[sizeof Trains];
    starting = 0;
    arriving = 0;

    if ((f = fopen(argv[1], "r")) == NULL){

        fprintf(stderr, "The file could not be opened.\n");
        abort();
    } //end check file
    else {

       if (argc != 2 && argc != 4){

        fprintf(stderr, "Wrong number of arguments.\n");
        abort();
        } //check correct number of arguments


        for (i = 0; i < MAX_SIZE && !(feof(f)) ; i++){

            fgets(whole_line, sizeof Trains[i], f);

            sscanf(whole_line, "%s", Trains[i].departure);
            sscanf(whole_line, "%*s%d.%d.%d", &Trains[i].hour_departure.hh,&Trains[i].hour_departure.mm,&Trains[i].hour_departure.ss);
            sscanf(whole_line, "%*s%*s%s", Trains[i].arrival);
            sscanf(whole_line, "%*s%*s%*s%d.%d.%d", &Trains[i].hour_arrival.hh,&Trains[i].hour_arrival.mm,&Trains[i].hour_arrival.ss);

            fprintf(stdout, "%s", whole_line);
        } //end for dump in struct

        i++;

        if (argc == 4){

        if (argv[2][0] == '-') {

            if (argv[2][1] != 'c') {

                printf("Wrong syntax.\n");
                abort();

            } //if syntax correct
            else {

            result = find_city(argv[3], &starting, &arriving, i, Trains);

            if (result == -1) {

            printf("The city was not found.\n");
            exit(EXIT_FAILURE);

            }//check result search

            else {
            printf("There ");
            if (starting == 1) printf("is %d train", starting);
            else printf("are %d trains", starting);
            printf(" departing from the starting city and %d arriving there.\n", arriving);

            }

            }
        } // if use option
        } // if parameter

    fclose((f));
    } //end else

    return 0;
} //end main

/*start function declaration */


int find_city(char city[20+1], int *start, int *arrive, int tot_rows, Table trains[]){

    int i;
    for (i = 0; i < tot_rows; i++){

    if (strcmp(city, trains[i].departure) == 0){

        *start+=1;
    }//end start if
    else if (strcmp(city, trains[i].arrival) == 0){

        *arrive+=1;

    }//end arrive if

    }//end for


    if (*arrive == 0 && *start == 0){

    return -1;

    }

    else return 0;
}
