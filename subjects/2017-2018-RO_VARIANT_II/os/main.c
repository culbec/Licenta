#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// relatie Parinte - 3 Copii
// fiecare copil incearca sa citeasca din pipe, cat timp exista writeri (cineva are deschis capatul de scriere al pipe-ului)
// parintele scrie in pipe cate un caracter, copii incearca sa citeasca
// nu avem garantia ca caracterele se vor afisa in ordine, deoarece depinde cine reuseste sa citeasca primul din pipe
// programul se va bloca deoarece cele 3 procese copil nu inchid capatul de scriere inainte sa inceapa sa citeasca
// astfel ele vad ca mai exista cineva care incearca sa scrie, asteptand input

//* a) HIERARCHY
//      i = 0   ----- C1
//
//
//  P   i = 1   ----- C2
//
//
//      i = 2   ----- C3

//* b) Ce se va afisa la executie? Fiecare litera de la 'a' la 'j' pe cate o linie, in ordine nedeterministica
// Programul se va bloca si nu isi va duce la bun sfarsit executia

//* c) De ce nu se termina procesele fiu?
// Deoarece capatul de scriere al pipe-ului este deschis in acestea cat timp se face citirea, astfel chiar daca
// parintele inchide acel capat si opreste stream-ul de date, copiii vad ca exista procese care au capatul de scriere
// deschis, astfel ele asteapta date chiar daca nu are cine sa le trimita

//* d) Intre ce linii ati muta linia 11 astfel incat procesele fiu sa se termine?
// Liniile 6-7

//* e) Explicati linia 21
// Linia 21 while(wait(NULL) > 0) {} executa wait in parinte cat timp parintele primeste inapoi PID-ul copilului care si-a schimbat statusul
// Daca wait(NULL) < 0, atunci avem eroare, ceea ce poate semnala fie ca nu mai sunt copii (errno = ECHILD), fie ca s-a intampinat o alta eroare
// Daca errno != ECHILD, oricum se termina programul, dar putem avea procese orfan
int main()
{
    int pfd[2], i;
    char buffer, c;
    pipe(pfd);
    for (i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {
            close(pfd[1]);
            while (read(pfd[0], &buffer, 1) > 0)
            {
                printf("%c\n", buffer);
            }
            close(pfd[0]);
            exit(0);
        }
    }

    close(pfd[0]);
    for (i = 0; i < 10; i++)
    {
        c = 'a' + i;
        write(pfd[1], &c, 1);
    }
    close(pfd[1]);
    while (wait(NULL) > 0)
    {
    }
    exit(0);
}