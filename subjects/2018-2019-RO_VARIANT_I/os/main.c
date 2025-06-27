#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int n = 0, a[2], b[2];

void w(int p[2], char c)
{
    // the variable n is global and thus is incremented here, by the caller of the function
    n++;
    // caller creates a child process, the if block is executed by the child process
    // the child process closes the input stream of the pipe and writes the passed c character to the output stream of the pipe
    // the child process exits with exit code 0
    if (fork() == 0)
    {
        close(p[0]);
        write(p[1], &c, 1);
        close(p[1]);
        exit(0);
    }
}

void r(int p[2])
{
    char c;
    // the variable n is global and thus is incremented here, by the caller of the function
    n++;

    // caller creates a child process, the if block is executed by the child process
    // the child process closes the output stream of the pipe and reads from the input stream into the character variable c
    if (fork() == 0)
    {
        close(p[1]);
        // read returns the numbers of characters read, a number between [0, max_buf_size]
        // returns -1 on error
        // the child process reads 1 byte from the pipe and then closes the input stream
        if (read(p[0], &c, 1) > 0)
        {
            printf("%c\n", c);
        }
        close(p[0]);
        exit(0);
    }
}

//* a) HIERARCHY
//
//      ---     w(a, 'x')       --- C1
//
//  P   ---     w(a, 'y')       --- C2
//
//      ---     r(a)            --- C3
//
//      ---     r(a)            --- C4
//*

//* b) What is the output of the program?
// The program is feeding the characters 'x' and 'y' into a pipe, through two separate child processes,
// characters which will be polled through another two child processes
// Depending on which child process writes the character first, and if the program succeeds in all calls, the output can be:
//* x
//* y
//* 4
// or
//* y
//* x
//* 4

//* c) Ce afiseaza executia programului daca linia 21 este inlocuita cu codul de mai jos
// w(a, 'x'); w(b, 'y'); r(a); r(b);
//* Fiind apeluri secventiale din parinte, se va afisa prima data ceea ce s-a scris in a, iar dupa ceea ce s-a scris in b
//* x
//* y
//* 4

//* d) Ce afiseaza executia programului daca linia 21 este inlocuita cu codul de mai jos
// w(a, 'x'); w(a, 'y'); r(a); r(b);
//* Fiindca se scrie doar in pipe a, citirea din b va returna 0 bytes cititi, pentru ca se inchid toti cei care ar putea scrie in pipe
//* x
//* 4
// or
//* y
//* 4

//* e) Explicati functionarea programului daca se inlocuieste linia 21 ca la punctul d) si in plus se mai elimina linia 22
// Apelurile read si write sunt blocante, in urmatorul sens:
// - read este blocant pana cand se scrie ceva in pipe sau pana cand nu mai exista scriitori;
// - write este blocant pana cand se face loc in pipe;
// Astfel, la punctul d) programul se termina deoarece pipe-ul era inchis in procesul parinte, astfel nu mai existau scriitori,
// iar read() returna 0 in procesul copil care ar fi vrut sa citeasca
// Insa daca scoatem linia 22, pipe-urile vor ramane deschise in parinte, la ambele capete
// Nu este o problema pentru pipe-ul a, pentru ca are cine sa citeasca din el,
// insa este o problema pentru pipe-ul b care nu contine date
//* Raspuns: deadlock, se afiseaza 'x\n' si dupa programul se blocheaza pana cand b ar primi date prin acel pipe cumva
int main(int argc, char **argv)
{
    // the parent creates two pipes: a and b
    pipe(a);
    pipe(b);

    // as the file descriptors are inherited in the child processes
    // each child process will have both ends opened, and they will write their characters into the pipe and exit
    w(a, 'x');
    w(a, 'y');

    // then, another two child processes are polling data from the pipes, 1 byte at a time
    r(a);
    r(a);

    close(a[0]);
    close(a[1]);
    close(b[0]);
    close(b[1]);
    // the parent process waits for all child processes to end
    // the variable n will be incremented each time a child is created, supposing the fork() succeeds
    // if the fork() fails, the wait call will return with error each time the parent process tries to wait for a non-existing child
    for (int i = 0; i < n; i++)
    {
        wait(0);
    }

    // the parent process prints how many children it tried to launchs
    printf("%d\n", n);
    return 0;
}