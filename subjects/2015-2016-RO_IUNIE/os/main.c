#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//* a) Variabila n poate lua valorile:
// -1: daca fork() da fail
// 0: cand suntem in procesul copil
// pid_t number: cand suntem in procesul parinte, PID-ul copilului nou creat

//* b) Ce vor afisa pe ecran urmatoarele rulari, considerand ca directorul personal
//* al utilizatorului nu se afla in variabila de mediu PATH.
// b.1) grep grep grep.c - va afisa linia cu execlp...
// b.2) ./grep grep grep.c:
//  inainte
//  execlp...
//  ceva
// b.3) ./grep grep
//  inainte
//  dupa

int main(int c, char **v)
{
    int p[2], n;
    char s[10] = "ceva";
    pipe(p);
    n = fork();
    if (n == 0)
    {
        close(p[0]);
        printf("inainte\n");
        if (c > 2)
        {
            execlp("grep", "grep", v[1], v[2], NULL);
        }
        strcpy(s, "dupa");
        write(p[1], s, 6);
        close(p[1]);
        exit(0);
    }
    close(p[1]);
    read(p[0], s, 6);
    close(p[0]);
    printf("%s\n", s);
    return 0;
}