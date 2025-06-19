// Se da fragmentul de cod de mai jos. Indicati liniile care se vor tipari pe ecran in ordinea in care vor aparea,
// considerand ca apelul sistem fork se executa cu succes? Justificati raspunsul.
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//* RASPUNS
//* Procesul parinte si cei 2 copii ai sai for afisa PID: i curent pe ecran
//* Nu putem garanta cand se va face flush pe stdout, astfel ca nu vom putea garanta ordinea de tiparire
//* Daca presupunem ca procesele se executa in paralel, pornind imediat dupa instantiere (in cazul copiilor),
//* si ca se face flush instant pe stdout, se poate tipari:
//*
//* PID_PARINTE: 0\n
//* PID_COPIL1: 0\n
//* PID_PARINTE: 1\n
//* PID_COPIL2: 1\n
//*
//* Daca nu au loc aceste presupuneri, este posibil ca output-ul sa fie intercalat ===> PID_PROCES_CURENT: i_curent\n, in oricare ordine
int main() {
    int i; // global context

    for (i = 0; i < 2; i++) {
        // PID_PROCES_CURENT: i\n
        printf("%d: %d\n", getpid(), i);
        
        if (fork() == 0) {
            // in child
            // PID_CHILD: i\n
            printf("%d: %d\n", getpid(), i);
            exit(0); // child exits
        }
    }

    // in parent
    // waiting for all children to end
    for (i = 0; i < 2; i++) {
        wait(0);
    }

    return 0;
}