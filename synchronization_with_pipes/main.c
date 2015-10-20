#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

typedef int * Semaphore;


Semaphore sA, sB, sC, sD, sE, sF, sG, sH, sI;

Semaphore INIT() {

    Semaphore  s;
    s = (Semaphore) malloc (1 * sizeof(Semaphore));

    pipe(s);
    return s;
}

void WAIT (Semaphore s) {
    int  junk;
    if (read (s[0], &junk, 1) <= 0) {
        fprintf(stderr, "Error: WAIT \n");
        exit(1);
    }
}

void SIGNAL (Semaphore s) {
    if (write(s[1], 1, 1) <= 0) {
        fprintf(stderr, "Error: SIGNAL\n");
        exit(1);
    }
}

void DESTROY (Semaphore s) {
    free(s);
}

void pfA(){
    WAIT(sA);
    Sleep(1);
    printf("A\n");
    SIGNAL(sB);
    SIGNAL(sB);
    SIGNAL(sB);
    exit(0);
}
void pfB(){
    WAIT(sB);
    Sleep(1);
    printf("B\n");
    SIGNAL(sI);
    exit(0);
}
void pfC(){
    WAIT(sB);
    Sleep(1000);
    printf("C\n");
    SIGNAL(sC);
    SIGNAL(sC);
    exit(0);
}
void pfD(){
    WAIT(sB);
    Sleep(1000);
    printf("D\n");
    SIGNAL(sD);
    exit(0);
}
void pfE(){
    WAIT(sC);
    Sleep(1000);
    printf("E\n");
    SIGNAL(sG);
    exit(0);
}
void pfF(){
    WAIT(sC);
    Sleep(1000);
    printf("F\n");
    SIGNAL(sG);
    exit(0);
}
void pfG(){
    WAIT(sG);
    WAIT(sG);
    Sleep(1000);
    printf("G\n");
    SIGNAL(sI);
    exit(0);
}
void pfH(){
    WAIT(sD);
    Sleep(1000);
    printf("H\n");
    SIGNAL(sI);
    exit(0);
}
void pfI(){
    WAIT(sI);
    WAIT(sI);
    WAIT(sI);
    Sleep(1000);
    printf("I\n");
}

int main()
{
    pid_t pA, pB, pC, pD, pE, pF, pG, pH, pI;

    sA = INIT();
    sB = INIT();
    sC = INIT();
    sD = INIT();
    sE = INIT();
    sF = INIT();
    sG = INIT();
    sH = INIT();

    pA = fork();
    if (pA != 0) {
        pB = fork();
        if (pB != 0) {
            pC = fork();
            if (pC != 0){
                pD = fork();
                if (pD != 0) {
                    pH = fork();
                    if (pH != 0) {
                        pfI();
                    } else {
                        pfH();
                    }
                } else {
                    pfD();
                }
            } else {
                pE = fork ();
                if (pE != 0) {
                    pfC();
                } else {
                    pF = fork ();
                    if (pF != 0) {
                        pfE();
                    } else {
                        pG = fork ();
                        if (pG != 0) {
                            pfF();
                        } else pfG();
                    }
                }
            }
        } else pfB();
    } else pfA();

    return 0;
}
