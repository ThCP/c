/*

Write a program for the management of a book of contacts of maximum 100 contacts.
The program shall allow the storage of following data in a structure:
typedef struct names {
char name[20];
char surname[20];
char number[20];
char mobile[20];
} Names;
/*Name*/
/*Surname*/
/*Phone Number*/
/*Mobile Number*/
/*The program shall allow the user to perform, by means of a menu, the input of a new
contact (allowing eventual duplicates of name and surname, but shall give a warning
to the user in case of duplicates and shall ask to confirm the input), and displays the
complete list.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2

typedef struct names {
char name[20];
char surname[20];
char number[20];
char mobile[20];
} Names;

int checkName (char name[], Names entryCheck[]);


int main()
{
    Names PhoneBook[100];
    int i;
    char surname[20], name[20];
    int result = 1;
    char dump;
    fprintf(stdout, "This program manages a phone book containing at most 100 contacts\n");
    fprintf(stdout, "Please insert the names in the book as following\n");
    // scanf("%c", &dump);


    for (i = 0; i < MAX_SIZE; i++){

        fprintf(stdout, "Insert surname, max 20 characters\n");
        fgets(surname, 20, stdin);
        fflush(stdin);
       // scanf("%c", &dump);


        result = checkName(surname, PhoneBook);
        if (result == 1){

            strcpy(PhoneBook[i].surname, surname);
            fprintf(stdout, "Insert name, max 20 characters\n");
            scanf("%c", &dump);
          //  fflush(stdin);
            fgets(PhoneBook[i].name, 20, stdin);
            result = checkName(name, PhoneBook);
            if (result == 1){

                fprintf(stdout, "Insert number, max 20 characters\n");
                fgets(PhoneBook[i].number, 20, stdin);
                fprintf(stdout, "Insert mobile, max 20 characters\n");
                fgets(PhoneBook[i].mobile, 20, stdin);

            }//end check name
        }//end check surname
        if (result == 0){

            fprintf(stdout, "Contact already present, skipping.\n");
            i--;
        }

    fflush(stdin);


    }//end for

    for (i = 0; i < MAX_SIZE; i++){

        fprintf(stdout, "Entry number %d\n", i+1);
        fprintf(stdout, "Name: %s", PhoneBook[i].name);
        fprintf(stdout, "Surname: %s", PhoneBook[i].surname);
        fprintf(stdout, "Home number: %s", PhoneBook[i].number);
        fprintf(stdout, "Mobile: %s", PhoneBook[i].mobile);

    }

    return 0;
}

int checkName (char name[], Names entryCheck[]){

    int i, result;

    for (i = 0; i < MAX_SIZE; i++){

        if (strcmp (name, entryCheck[i].surname) == 0){

            fprintf(stdout, "Last string was already present in the phonebook.\n");
            fprintf(stdout, "Insert 1 to write anyway or 0 to skip entry.\n");
            fscanf(stdin,"%d", &result);

            return result;
        }//end if


    }//end for

    return 1;

}//end function
