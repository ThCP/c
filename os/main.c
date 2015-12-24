#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    FILE *finn;
    char c;
    char buffer[20];

    if (argc != 2) {
        fprintf(stderr, "Wrong number of parameters.\n");
        exit(1);
    }

    finn = fopen(argv[1], "r");

    if (finn == NULL) {
        fprintf(stderr, "The file could not be opened");
        exit(1);
    }

    printf("With fgetc()\n");

    while ((c = fgetc(finn)) != EOF ) {
        printf("%c", c);
    }

    printf("With fgets()\n");

    fclose (finn); // I close and reopen the file so that I can start from the beginning

    finn = fopen(argv[1], "r");

    if (finn == NULL) {
        fprintf(stderr, "The file could not be opened");
        exit(1);
    }


    while (fgets (buffer, 20, finn) != NULL) {
        printf("%s", buffer);
    }


    return 0;
}
