#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

//* EXPLICATIE RULARE
// Primul proces fiu primeste ca input stream fisierul 'fa', iar ca append stream fisierul 'fb'
// Procesul care va executa sortarea (C1 sa zicem), va ramane blocat cat timp fisierul 'fa' este folosit de
// un alt proces, adica de cel care scrie argumentele in 'fa' (C2 sa zicem); C2 va scrie fiecare argument din linia de comanda
// si il va scrie in 'fa' urmat de '\n', adica va pune toate argumentele din linia de comanda in 'fa' pe linii separate
// Procesul care citeste rezultatele din 'fb' (C3 sa zicem) va poll-ui maxim 32 de caractere din fisierul 'fb' si le va
// afisa pe stdout, in 'fb' fiind deja argumentele sortate
// Daca 'fa' si 'fb' erau doua fisiere obisnuite si nu FIFO, atunci la rulari diferite exista sansa ca
// output-ul sa fie diferit, deoarece nu s-ar fi facut flush in fisiere
// Daca erau fisiere obisnuite, abia dupa prima rulare ar fi aparut date in fisier, sort nemaiasteptand sa fie populat 'fa' deoarece vede
// ca nu este PIPE sau FIFO si astfel presupune ca este un fisier as it is

//* a) Ce va afisa executia de mai jos? Justificati raspunsul.
//* ./a.out a d b c
// "a b c d", fiecare caracter pe linii separate

//* b) Cum e afectata executia daca blocul IF de pe liniile 8-16 este mutat intre liniile 3-4? Justificati raspunsul.
// Se refera la IF-ul care lanseaza procesul ce va scrie in FIFO-ul 'fa'. N-ar trebui sa afecteze executia? (nu afecteaza)

//* c) Ce va afisa executia de mai jos, daca in linia 20 cifra 1 este schimba in 2? Justificati raspunsul.
//* ./a.out y z x > /dev/null
// Daca se schimba din 1 in 2, atunci se va scrie rezultatul in stderr
// Redirectarea din linia de mai sus are loc pentru stdout, nu pentru stderr
// Se va afixa "x y z", pe linii separate, dar pe stderr, nu pe stdout

//* d) Cum va fi afectata executia daca linia 14 este comentata? Justificati raspunsul.
// daca se comenteaza close(fa), in teorie nu ar trebui sa fie afectata executia
// procesul copil care ar scrie in FIFO-ul 'fa' isi va opri executia si va opri teoretic accesul la FIFO
// astfel copilul care sorteaza ar trebui sa ruleze imediat dupa ce acest copil se termina
// daca presupunem ca accesul la FIFO nu este revocat dupa ce se termina procesul, atunci se va bloca executia
// programului deoarece procesul care sorteaza asteapta dupa 'fa', iar fisierul care printeaza pe stdout asteapta dupa 'fb',
// care va fi blocat de 'sort'

//* e) Cum va fi afectata executia programului daca liniile 4, 6 si 7 sunt comentate? Justificati raspunsul?
// adica liniile care lanseaza procesul bash care va sorta
// se va pastra doar 'execlp("bash", "bash", "-c", "sort < fa >>fb", NULL);', iar asta inseamna ca se va lansa un nou proces
// in locul parintelui, care va sorta continutul lui 'fa' si il va concatena la 'fb'
// 'fa' si 'fb' fiind FIFO-uri, executia se va bloca deoarece stream-urile din 'fa' si 'fb' vor fi goale, nemaiavand cine sa le deschida

int main(int argc, char **argv)
{
    int fa, fb, k;
    char s[32];

    // sorteaza ce se scrie in fisierul 'fa' si concateneaza la fisierul 'fb'
    if (fork() == 0)
    {
        execlp("bash", "bash", "-c", "sort < fa >>fb", NULL);
        exit(0);
    }

    if (fork() == 0)
    {
        // deschide un FIFO pentru WRITE_ONLY
        // si scrie pe rand toate argumentele din linia de comanda (exceptie nume program)
        // in 'fa', pe linii separate
        fa = open("fa", O_WRONLY);
        for (k = 1; k < argc; k++)
        {
            write(fa, argv[k], strlen(argv[k]));
            write(fa, "\n", 1);
        }
        close(fa);
        exit(0);
    }

    if (fork() == 0)
    {
        // deschide un FIFO pentru READ_ONLY
        // si citeste maxim 32 de caractere din fisierul 'fb'
        // iar apoi scrie in stdout cate caractere a citit, cat timp sunt caractere in
        // FIFO
        fb = open("fb", O_RDONLY);
        while ((k = read(fb, s, 32)) > 0)
        {
            write(1, s, k);
        }
        close(fb);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}