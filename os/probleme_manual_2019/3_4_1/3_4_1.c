// a. Descrieti pe scurt functionarea apelului sistem fork si valorile pe care le poate returna
// Apelul sistem fork se foloseste in cadrul proceselor pentru a paraleliza executia unui anumit proces.
// Procesul parinte apeleaza fork pentru a crea un nou proces (denumit fiu), cei doi fiind intr-o relatie parinte-fiu.
// In momentul in care functia sistem fork este apelata, imaginea procesului parinte este
// copiata intr-un alt proces al aceluiasi program executat, cele doua procese executandu-se in paralel incepand
// cu instructiunea ce urmeaza apelul functiei sistem fork.
// Apelul sistem poate esua cand:
//  * nu exista suficienta memorie pentru a crea o copie a imaginii procesului curent;
//  * succesul executiei functiei sistem fork duce la depasirea numarului maxim de procese admis;
// In urma executiei, functia sistem fork poate returna urmatoarele valori:
//  * -1        ->  eroare, variabila errno fiind populata cu codul de eroare corespunzator;
//  * 0         ->  pentru procesul copil; procesul copil isi poate interoga PID-ul si PID-ul parintelui prin functiile getpid() si getppid();
//  * pid_t PID ->  pentru parinte; se returneaza PID-ul procesului copil nou creat;
// Contextul procesului parinte se copiaza in copil (pana la apelul fork inclusiv): acest lucru se intampla deoarece imaginea procesului parinte
// se copiaza in procesul copil.

// b. Ce tipareste pe ecran secventa de program de mai jos, considerand ca apelul sistem fork se executa cu succes? Justificati raspunsul.
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//* RESPONSE: PID_PARENT: 3\n
int main() {
    int n = 1; // shared context
    if (fork() == 0) { // in child
        n = n + 1;
        exit(0); // child exits with returncode = 0
    }

    // in parent
    n = n + 2;
    printf("%d: %d\n", getpid(), n);

    // we need to wait for the child processes to finish
    // if we do not wait, the child processes can go into 'orphan' or 'zombie' states:
    //  * orphan state: the parent finished before the child;
    //  * zombie state: the child finishes, but no one collected its state; the child process appears in the process table
    //  *               and it is assigned automatically to the init process (PID==1)
    //! wait(int &status) waits until one of the parent's children is changing its status, in case which the status variable is populated with the child's status
    //* that said, the we need to call wait until all children have finished, or until an error, wait returning:
    //  * -1            -> error, in which case the errno is populated with the returncode; if errno == ECHILD ===> there are no children left ===> all children finished;
    //  * pid_t pid     -> the PID of the child which changed its status;
    wait(0);

    return 0;
}