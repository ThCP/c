/**
    Modified linux shell.
    MyShell receives commands on the command line: they are then executed by background processes
    which write the result on a file called <PID>.log where <PID> is the identifier of the child
    process.
    The shell terminates when the "exit" command is entered.

    SysProg2

    Riccardo Cappuzzo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


#define MYBUF 1024

char ** my_com_mat_alloc (int n);
char ** read_commands (char * buffer);

int main(int argc, char ** argv)
{
    char buffer[MYBUF+1];
    char ** commands, output_file[MYBUF+1];
    pid_t pid;
    int fd;

    printf("MyShell usage:\nInsert the command and press enter.\nThe result is stored in a file called <PID>.log where <PID> is the child process' pid.\nWrite \"exit\" to leave MyShell.\n");

    printf(": ");
    fgets(buffer, MYBUF, stdin); // read the commands from stdifn

    while (strcmp(buffer, "exit\n") != 0) {
        commands = read_commands(buffer);

        pid = fork();

        if (pid == 0) {
            // child process
            sprintf(output_file, "%d.log", getpid());
            fd = open(output_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // create the log file

            close(1); // close the stdout fd
            dup(fd); // use the new file as a dummy stdout

            execvp (commands[0], commands); // exec the new commands
        } else {
            // parent process
            // no wait for bg processes
            printf(": ");
            fgets(buffer, MYBUF, stdin); // read the commands from stdifn
        }
    }
    return 0;
}

char ** my_com_mat_alloc (int n) {
    char ** nP = NULL;
    int i;

    nP = malloc((n) * sizeof(char *)); // allocate an array of pointers

    if (nP == NULL) {
        fprintf(stderr, "Unable to create pointer.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) { // for each entry in the pointer array allocate the buffer space
        nP[i] = malloc ((MYBUF+1) * sizeof(char));
        if (nP[i] == NULL) {
            fprintf(stderr, "Unable to create pointer.\n");
            exit(EXIT_FAILURE);
        }
    }
    return nP;
}

char ** read_commands (char * buffer) {
    char *tok;
    char ** commands;
    char * buf_short;
    int last, n_commands = 0, i;

    buf_short = strrchr(buffer, '\n'); // find the last occurrence of "\n" character

    last = buf_short-buffer; // find the index of the last "\n"
    buffer[last] = '\0'; // truncate the buffer at the last "\n"

    buf_short = malloc ((last+1) * sizeof(char)); // allocate a copy of the buffer (for strtok function)

    strcpy(buf_short, buffer);

    tok = strtok(buf_short, " "); // find the total number of parameters
    while (tok != NULL) {
        n_commands++;
        tok = strtok(NULL, " ");
    }

    commands = my_com_mat_alloc(n_commands+1); // allocate the command matrix with n commands + 1 sentinel

    tok = strtok(buffer, " "); // fill the command matrix
    for (i = 0; i < n_commands; i++) {
        strcpy(commands[i], tok);
        tok = strtok(NULL, " ");
    }

    commands[n_commands] = (char *) 0; // put the sentinel in the last position

    return commands;

}
