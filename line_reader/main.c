#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define BUFLEN 1024+1


void read_file (char * input, char *output);
void get_names (char *input, char *output, FILE * fpar);

int main(int argc, char ** argv)
{
    FILE * fpar;
    char input[BUFLEN], output[BUFLEN];
    fpar = fopen("parametri.txt", "r");

    if (fpar == NULL) {
        fprintf(stderr, "File \"parametri.txt\" non trovato nella cartella.\n");
        printf("Il programma richiede un file di testo chiamato \"parametri.txt\" nella cartella di esecuzione.\n");
        printf("La prima riga del file deve contenere il nome del file di input, la seconda riga il nome del file di output.\n");
        printf("Premere invio per terminare.\n");

        scanf("%*c");

        return 1;
    }

    get_names(input, output, fpar);
    fclose (fpar);

    read_file (input, output);

    return 0;
}


void read_file (char *input, char *output) {

    char buffer[BUFLEN];
    int id;
    int i;
    FILE * fout, *finn;

    finn = fopen (input, "r");
    if (finn == NULL) {
        fprintf(stderr, "Il file di input non è presente nella cartella.\n");
        exit(1);
    }

    fout = fopen (output, "w");
    if (fout == NULL) {
        fprintf(stderr, "Impossibile creare il file di output.\n");
        exit(1);
    }

    fgets(buffer, BUFLEN, finn); // tengo la prima riga rimuovendo il FF
    buffer[0] = ' ';

    fprintf(fout, "%s", buffer); // stampo l'header nel file di output

    while (fgets (buffer, BUFLEN, finn) != NULL){
        //printf("%s\n", buffer);
        for (i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == 12) {
                buffer[i-1] = '\n';
                buffer[i] = '\0';
                break;
            }
        }

        if (sscanf(buffer, "%d %*s %*d %*d %*d %*d %*d %*d", &id) == 1){
            fprintf(fout, "%s", buffer);
        }
    }

    fclose (finn);
    fclose (fout);

    return;
}

void get_names (char *input, char *output, FILE * fpar) {
    fscanf(fpar, "%s", input);
    fscanf(fpar, "%s", output);
}
