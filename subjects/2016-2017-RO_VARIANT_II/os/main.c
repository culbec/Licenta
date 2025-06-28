#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

//* a) HIERARCHY
// P ---- C

//* b) Dati fiecare linie afisata de program, impreuna cu procesul care o tipareste
// P ----- Result:
// C ----- exam passed

//* c) Cate caractere sunt citite din pipe?
// 15

//* d) Cum este afectata terminarea proceselor daca lipseste linia 20?
// Procesul copil va ramane blocat deoarece procesul parinte inca are capatul de scriere deschis, asteptand input
// Procesul parinte asteapta ca copilul sa isi schimbe statusul, ceea ce nu se va intampla deoarece procesul copil ramane blocat
// Nu se termina niciunul

//* e) Cum este afectata terminarea proceselor daca lipsesc liniile 20 si 21
// Linia 20 explicata mai sus, daca linia 21 'wait(NULL);' lipseste, atunci parintele se termina, iar copilul ramane orfan pana cand
// se termina parintele, al carui capat de scriere va fi inchis by default cand se termina procesul parinte
// Cand se termina procesul parinte, copilul se va termina de asemenea
int main()
{
    int p[2], i = 0;
    char c, s[20];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        // poate continua la infinit daca read fails (read == -1)
        while (read(p[0], &c, sizeof(char)))
        {
            if (i < 5 || i > 8)
            {
                printf("%c", c);
            }
            i++;
        }
        printf("\n");
        close(p[0]);
        exit(0);
    }
    printf("Result: \n");
    strcpy(s, "exam not passed");
    close(p[0]);
    write(p[1], s, strlen(s) * sizeof(char));
    close(p[1]);
    wait(NULL);
    return 0;
}