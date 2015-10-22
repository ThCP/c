/*

Si scriva un programma in linguaggio C che legga il contenuto di un file
dopo averne ricevuto il nome da linea di comando. Il numero di righe del
file sia al massimo 80 e ciascuna riga del file contenga i seguenti campi,
ciascuno composto al massimo da 20 caratteri e privo di spazi
<materia> <nome prof> <cognome prof> <periodo> <crediti> <% superamento esame>
Il programma dovrà stampare a video:
a. il nome della materia che assegna più crediti in assoluto
b. per ciascun periodo didattico (considerandone al massimo 4), la
materia più difficile da superare
Il programma dovrà infine richiedere l’inserimento da tastiera di un
cognome di professore (massimo 20 caratteri) e stampare a video:
c. la somma dei crediti assegnati dalle materie che insegna
d. la media di superamento degli esami da lui tenuti.
Approfondimento: nei punti a) e b), se si verificasse il caso in cui siano
presenti due o più materie che assegnano il numero massimo di crediti o
abbiano nello stesso periodo il minor tasso di superamento, il programma
dovrà stampare l’elenco completo delle materie identificate

LAIB 11

05-06-13

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 80

struct _SUBJECT {

    char name[20];
    char prof_name[20];
    char prof_surname[20];
    int period;
    int credits;
    int success100;
};

/*PROTOTYPES*/

void print_results (struct _SUBJECT exam);
void find_maxCredits (struct _SUBJECT exam[], int tot_rows);
void find_hardestSubject (struct _SUBJECT exam[], int tot_rows);

int tot_credits (struct _SUBJECT exam[], char surname[20], int tot_rows);
float average_success (struct _SUBJECT exam[], char surname[20], int tot_rows);



int main(int argc, char *argv[])
{
    int i, credit_sum;
    float average;
    FILE *f;
    struct _SUBJECT examData[ROWS];
    char whole_line[100+1];
    char teacher_name[20];
    f = fopen(argv[1], "r");
    if   (f == NULL){

        printf("The file could not be opened.\n");
        abort();

    }   //end if check file open

    else {

        printf("The exam list is: \n");
        printf("%-15s\t%s\t%-15s\t%-10s\t%-5s\t%-5s\t%-5s\n", "Name", "Prof name", "Prof surname", "Period", "Credits","Success Percentage\n");

        for (i = 0; (i < ROWS) && (!feof(f)); i++){

            fgets(whole_line, 100+2, f);
            sscanf(whole_line, "%s%s%s%d%d%d", examData[i].name,examData[i].prof_name,
                                                    examData[i].prof_surname,&examData[i].period,
                                                        &examData[i].credits,&examData[i].success100);

        if (!feof(f)){
        print_results(examData[i]);
        }//end if

        }//end for

    i--;

    find_maxCredits(examData, i);
    find_hardestSubject(examData, i);

    printf("Insert professor's surname:\n");
    scanf("%s", teacher_name);

    credit_sum = tot_credits(examData, teacher_name, i);
    average = average_success(examData, teacher_name, i);

    printf("The total number of credits given by this professor is %d.\n", credit_sum);
    printf("The average success rate is %g.\n", average);

    fclose(f);

    } //end else fopen

    return 0;
}


/*FUNCTIONS*/

void print_results(struct _SUBJECT exam){

    printf("%-15s %-15s %-15s %-5d %-5d %-5d\n", exam.name, exam.prof_name,exam.prof_surname,exam.period,exam.credits,exam.success100);
}//end function

void find_maxCredits (struct _SUBJECT exam[], int tot_rows){

    int i, j = 1;
    int max_credit = 0;
    int pos = 0;
    int pos_array[ROWS];

    max_credit = exam[0].credits;
    pos_array[0] = 0;

    for (i = 1; i < tot_rows ; i++){


        if (max_credit == exam[i].credits){

        pos_array[j] = i;
        j++;

        }

        else if (max_credit < exam[i].credits){
            max_credit = exam[i].credits;
            pos = i;
            j = 1;
        }//end if

    }//end for

    if (j != 1){

    printf("The exams which yeld more credits are: \n");

        for (i = 0; i < j; i++){

            print_results(exam[pos_array[i]]);

        }

    }
    else {

    printf("The exam which yelds more credits is: \n");
    print_results(exam[pos]);

    }

}//end function

void find_hardestSubject (struct _SUBJECT exam[], int tot_rows){


    int i, j = 1;
    int min_passed = 0;
    int pos = 0;
    int pos_array[ROWS];

    min_passed = exam[0].success100;
    pos_array[0] = 0;

    for (i = 1; i < tot_rows ; i++){


        if (min_passed == exam[i].success100){

        pos_array[j] = i;
        j++;

        }

        else if (min_passed > exam[i].success100){
            min_passed = exam[i].success100;
            pos = i;
            j = 1;
        }//end if

    }//end for

    if (j != 1){

    printf("The exams with the lowest success rate are: \n");

        for (i = 0; i < j; i++){

            print_results(exam[pos_array[i]]);

        }

    }
    else {

    printf("The exam with the lowest success is: \n");
    print_results(exam[pos]);

    }


}//end function

int tot_credits (struct _SUBJECT exam[], char surname[20], int tot_rows){

    int i, credit_sum = 0;

    for (i = 0; i < tot_rows; i++){

        if (strcmp (surname, exam[i].prof_surname) == 0){

            credit_sum += exam[i].credits;

        }//end if

    }//end for

    return credit_sum;

}//end function

float average_success (struct _SUBJECT exam[], char surname[20], int tot_rows){

    float average;
    int sum, i, count = 0;
    sum = 0;
    for (i = 0; i < tot_rows; i++){

        if (strcmp(surname, exam[i].prof_surname) == 0){

            sum += exam[i].success100;
            count++;
        }//end if

    }//end for

    average = (0.0 + sum) / count;

    return average;

}//end function

