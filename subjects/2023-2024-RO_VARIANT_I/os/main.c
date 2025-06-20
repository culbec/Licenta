#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int n;
    char s[12];

    n = atoi(argv[1]);
    if (n > 0)
    {
        fork();
        if (wait(NULL) > 0)
        {
            sprintf(s, "%d", n - 1);
            execlp(argv[0], argv[0], s, NULL);
        }
        printf("%d\n", n);
    }

    return 0;
}

// a) explicati in detaliu functionarea liniei: 'execlp(argv[0], argv[0], s, NULL);'
// * Se executa printr-un nou proces acelasi program executat de procesul curent, primind ca lista de argumente (nume_program_curent_executat, s),
// * unde s este string-ul rezultat din sprintf(s, "%d", n-1)
// * Executia procesului intr-un nou proces este datorata conditiei 'if (wait(NULL) > 0)', care returneaza -1 eroare, cu errno == ECHILD daca nu mai sunt copii, sau PID copil care si-a schimbat starea
// * in parinte. Parintele se va bloca, copilul va iesi imediat cu -1 si va executa procesul.

// b) Cate procese creeaza executia de mai jos, excluzand procesul parinte initial? Justificati raspunsul?
// ./a.out 3

//* For each child: the wait(NULL) call will return with -1 and errno == ECHILD, as the child process has no children, and will not execute the same program
//* The same program will be executed with n - 1 only by the parent process, resulting in replacing the current process with a new one with decremented n
//* (P) n = 3 > 0 ... fork() ... C1 prints '3\n' and P ...execlp() with n = 2
//* (P) n = 2 > 0 ... fork() ... C2 prints '2\n' and P ...execlp() with n = 1
//* (P) n = 1 > 0 ... fork() ... C3 prints '1\n' and P ...execlp() with n = 0
//* (P) n = 0 == 0 ...STOP!
//*** NUMBER OF PROCESSES = num_fork() = 3
//! exec*() does not create a new process! it just replaces the current process with the image of the provided program!

// c) Ce va afisa procesul parinte in executia de mai jos? Justificati raspunsul.
// ./a.out 1

//* (P) n = 1 > 0 ... fork() ... C1 prints '1\n' and P ...execlp() with n = 0
//* (P) n = 0 == 0 ...STOP!
//*** PRINTED MESSAGE: 1\n

// d) Specificati liniile, in ordinea aparitiei, afisate de executia de mai jos. Justificati raspunsul.
// ./a.out 3

//* Presupunand ca copilul creat de ...fork()... nu este scos de pe procesor imediat dupa ce se verifica conditia, liniile vor fi:
//* 3
//* 2
//* 1
//* Altfel, ar putea aparea in orice ordine, conditie care depinde de cat timp pe procesor au fiecare C1, C2, C3 (fiind operatie IO, este o operatie grea care poate duce procesorul la blocarea procesului, in caz ca e un procesor slab)

// e) Specificati liniile, in ordinea aparitiei, afisate de executia de mai jos, daca pe linia 8 caracterul '>' se inlocuieste cu '<'. Justificati raspunsul.
// ./a.out 3

//* wait(NULL) < 0: corpul instructiunii if se va executa doar de copii, parintii asteapta, liniile vor fi:
//* 1
//* 2
//* 3