#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//* a) HIERARCHY
//      i = 1       ----- C1
//
//      i = 5       ----- C2
//
// P    i = 9       ----- C3
//
//      .....
//
//      i = 4K+1    ----- C_{K+1}

//* b) ./pr p q 1 x
// Se blocheaza procesul copil, deoarece se deschide prima data pt read, si nu deschide nimeni pt write

//* c) ./pr p q 1 x p q 0 y
// Primul proces copil va citi din p, va scrie in q
// Al doilea proces copil va scrie in p, va citi din q
// Nu se va bloca deoarece se deschid fisierele in ordinea in care trebuie
// Se va afisa 'x\ny\n' in orice ordine, depinde cine scrie si cine citeste prima data

//* d) O diagrama circulara care indica o posibilitate de deadlock
//           C1   C2
//           | \ / |
//      read | / \ | write
//           |/   \|
//           p     q
//      write       read
void f(char *a, char *b, int w, char *s)

//* e) ./pr p q 1 x q p 1 y
// Deadlock, C1 va astepta sa deschida cineva p pt scriere, iar C2 sa deschisa cineva q pt scriere
{
    // f va contine descriptori de fisier
    // w = 1 => r = 0 => f[0] READ, f[1] WRITE
    // w = 0 => r = 1 => f[1] READ, f[0] WRITE
    int f[2], r = 1 - w;
    char c;

    // copii scriu ceva intr-un fisier, citesc din alt fisier
    // si afiseaza ce au citit
    if (fork() == 0)
    {
        f[0] = open(a, w == 0 ? O_WRONLY : O_RDONLY);
        f[1] = open(b, w == 1 ? O_WRONLY : O_RDONLY);

        write(f[w], s, 1);
        read(f[r], &c, 1);

        printf("%c\n", c);
        close(f[0]);
        close(f[1]);
        exit(0);
    }
}

int main(int n, char **a)
{
    int i;
    for (i = 1; i < n; i += 4)
    {
        // nume fisier, nume fisier, read/write prin flag, char
        f(a[i], a[i + 1], a[i + 2][0] - '0', a[i + 3]);
    }

    // asteapta dupa copii
    for (i = 1; i < n; i += 4)
    {
        wait(0);
    }

    return 0;
}