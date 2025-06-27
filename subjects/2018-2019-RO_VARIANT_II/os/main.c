#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

bool search_pid(pid_t *pids, size_t size_pids, pid_t pid)
{
    for (size_t i = 0; i < size_pids; i++)
    {
        if (pids[i] == pid)
        {
            return true;
        }
    }
    return false;
}

#define SIZE_PIDS_F1 15
#define SIZE_PIDS_F2 4

pid_t *pids = NULL;

//* HIERARCHY
//
//      i = 0   ----- C1 (i = 1)        ----- C11 (i = 2)   ----- C111 (i = 3)                      STOP!
//                                      ----- C11 (i = 3)                                           STOP!
//              ----- C1 (i = 2)        ----- C12 (i = 3)                                           STOP!
//              ----- C1 (i = 3)                                                                    STOP!
//
// P    i = 1   ----- C2 (i = 2)        ----- C21 (i = 3)                                           STOP!
//              ----- C2 (i = 3)                                                                    STOP!
//
//      i = 2   ----- C3 (i = 3)                                                                    STOP!
//      i = 3                                                                                       STOP!
//*
void f1()
{
    int i;
    size_t curr_pids_index = 0;
    for (i = 0; i < 3; i++)
    {
        // the child does nothing and continues
        if (fork() == 0)
        {
        }

        if (!search_pid(pids, SIZE_PIDS_F1, getpid()))
        {
            printf("[i = %u] PID: %u | PARENT_PID: %u\n", i, getpid(), getppid());
            pids[curr_pids_index++] = getpid();
        }

        // the parent waits for its child to terminate
        // the child exits from wait(0) with errno == ECHILD, meaning that there
        // are no children to wait for
        wait(0);
        if (!search_pid(pids, SIZE_PIDS_F1, getpid()))
        {
            printf("[i = %u] PID: %u | PARENT_PID: %u\n", i, getpid(), getppid());
            pids[curr_pids_index++] = getpid();
        }

        // the child continues with the for loop, the parent waits for its child to finish
    }
}

//* HIERARCHY
//
//      i = 0   ----- C1 (i = 1)        ----- C11 (i = 2)   ----- C111 (i = 3)                      STOP!
//                                      ----- C11 (i = 3)                                           STOP!
//              ----- C1 (i = 2)
//              ----- C1 (i = 3)                                                                    STOP!
//
// P    i = 1
//
//
//      i = 2
//      i = 3                                                                                       STOP!
//*
void f2()
{
    int i, p = 0;
    size_t curr_pids_index = 0;
    for (i = 0; i < 3; i++)
    {
        // executes once in parent, p will then be set to the child's PID
        if (p == 0)
        {
            // p will be 0 in child, satisfying the forking condition
            // in the next iteration
            p = fork();
        }

        // parent will wait for the children to end
        wait(0);
        if (!search_pid(pids, SIZE_PIDS_F2, getpid()))
        {
            printf("[i = %u] PID: %u | PARENT_PID: %u\n", i, getpid(), getppid());
            pids[curr_pids_index++] = getpid();
        }
    }
}

//* HIERARCHY
//
//      i = 0   ----- C1 (i = 1)
//              ----- C1 (i = 2)
//              ----- C1 (i = 3)                                                                    STOP!
//
// P    i = 1   ----- C2 (i = 2)
//              ----- C2 (i = 3)                                                                    STOP!
//
//
//      i = 2   ----- C3 (i = 3)                                                                    STOP!
//      i = 3                                                                                       STOP!
//*
void f1_with_f2_hierarchy() {
    int i, p = getpid();
    size_t curr_pids_index = 0;
    for (i = 0; i < 3; i++)
    {
        // executes each time in the parent, because the parent will have another PID
        // on each iteration
        if (p != 0)
        {
            // p will be != 0 in parent, satisfying the forking condition
            // in the next iteration
            p = fork();
        }

        // parent will wait for the children to end
        wait(0);
        if (!search_pid(pids, SIZE_PIDS_F2, getpid()))
        {
            printf("[i = %u] PID: %u | PARENT_PID: %u\n", i, getpid(), getppid());
            pids[curr_pids_index++] = getpid();
        }
    }
}

int main()
{
    pids = (pid_t *)malloc(SIZE_PIDS_F1 * sizeof(pid_t));
    if (pids == NULL)
    {
        perror("malloc");
        exit(1);
    }

    pids = (pid_t *)memset(pids, 0, SIZE_PIDS_F1 * sizeof(pid_t));
    if (pids == NULL)
    {
        perror("memset");
        exit(1);
    }

    // a)
    printf("=============== f1() ===============\n");
    //f1();
    free(pids);
    pids = NULL;
    printf("\n");

    pids = (pid_t *)malloc(SIZE_PIDS_F2 * sizeof(pid_t));
    if (pids == NULL)
    {
        perror("malloc");
        exit(1);
    }

    pids = (pid_t *)memset(pids, 0, SIZE_PIDS_F2 * sizeof(pid_t));
    if (pids == NULL)
    {
        perror("memset");
        exit(1);
    }

    // b)
    printf("=============== f2() ===============\n");
    //f2();
    free(pids);
    pids = NULL;
    printf("\n");

    pids = (pid_t *)malloc(SIZE_PIDS_F2 * sizeof(pid_t));
    if (pids == NULL)
    {
        perror("malloc");
        exit(1);
    }

    pids = (pid_t *)memset(pids, 0, SIZE_PIDS_F2 * sizeof(pid_t));
    if (pids == NULL)
    {
        perror("memset");
        exit(1);
    }

    // c)
    printf("=============== f1_with_f2_hierarchy() ===============\n");
    f1_with_f2_hierarchy();
    free(pids);
    pids = NULL;
    printf("\n");

    // d) Apelul sistem 'wait(int &status)' are rolul de a bloca executia parintelui
    // pana cand unul din ai sai copii isi schimba starea
    // In caz de succes, returneaza PID-ul procesului copil care si-a schimbat starea, fiind populata variabila 'int& status'
    // cu statusul procesului copil
    // In caz de eroare, va returna -1 iar variabila errno va fi populata cu codul de eroare al apelului; ECHILD semnifica ca nu mai exista
    // copii dupa care sa se astepte
    // Aceasta functie asteapta dupa un singur copil sa isi schimbe starea, asa ca apelul trebuie facut
    // pana cand nu mai sunt copii care sa astepte, cu gestionarea erorilor in mod corespunzator

    return 0;
}