#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//* Copiii isi transmit PID-urile intre ei
//* C1 arata PID-ul rezultat din fork (0) + PID C2
//* C2 arata PID-ul rezultatin din fork(0) + PID C1
//* P arata PID C1 + PID C2

//* a) HIERARCHY
//      ---x==0--- C1
//      |
//      |
//  P   |
//      |
//      |
//      ---y==0--- C2
//*

//* b) Care proces va executa linia 11? Ce reprezinta valoarea variabilei m1 afisata?
// Primul proces creat de parinte (C1), reprezinta PID-ul celui de-al doilea copil creat de parinte (C2)

//* c) Care proces va executa linia 19? Ce reprezinta valoarea variabilei m2 afisata?
// Al doilea proces creat de parinte (C2), reprezinta PID-ul celui primului copil creat de parinte (C1)

//* d) Care dintre procese va executa linia 22? Ce reprezinta valorile variabilelor x si y afisate?
// Procesul parinte (P), x = PID_C1, y=PID_C2

//* e) Exista vreo relatie intre valoarea variabilei m1 din linia 11 si valoarea variabilei x din linia 22? Justificati raspunsul.
// Sunt PID-urile proceselor copil infratite: x=PID_C1, m1=PID_C2.

int main()
{
    int p1[2], p2[2], x, y, z, m1, m2;
    pipe(p1);
    pipe(p2);
    x = fork();
    // P creates C2
    if (x != 0)
        y = fork();
    // C1
    if (x == 0)
    {
        // PID of C1
        z = getpid();

        // C1 reads from p2, writes to p1
        close(p1[0]);
        close(p2[1]);
        write(p1[1], &z, sizeof(int));
        close(p1[1]);
        read(p2[0], &m1, sizeof(int));
        close(p2[0]);
        printf("x=%d: %d\n", x, m1);
        exit(0);
    }
    if (y == 0)
    {
        // PID of C2
        z = getpid();

        // C2 reads from p1, writes to p2
        close(p1[1]);
        close(p2[0]);
        write(p2[1], &z, sizeof(int));
        close(p2[1]);
        read(p1[0], &m2, sizeof(int));
        close(p1[0]);
        printf("y=%d: %d\n", y, m2);
        exit(0);
    }
    printf("x=%d, y=%d\n", x, y);
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}