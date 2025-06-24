#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int f; char c = 'a';

    // 3) rolul argumentelor
    // "fifo" -> path-ul catre fisierul FIFO care va fi creat
    // 0600 -> permisiunile, in cazul asta READ_WRITE pentru owner-ul fisierului (user-ul care ruleaza programul)
    mkfifo("fifo", 0600);
    // d) in ce situatie se va afisa 'a'?
    // cand apelul 'read' din copil esueaza
    // (barem zice ca niciodata, insa ar putea da fail daca nu se creeaza fifo-ul de exemplu sau daca esueaza read)
    if (fork() == 0) {
        // c) mkfifo("fifo", 0600)
        // daca parintele executa open inainte ca copilul sa creeze fifo, atunci
        // copilul se blocheaza la open, asteptand ca cineva sa deschide pentru WRITE_ONLY, iar parintele in wait
        f = open("fifo", O_RDONLY);

        // a) citeste un singur caracter din fifo -> 'x'
        // "x\n"
        read(f, &c, 1);
        printf("%c\n", c);
        close(f);
        // b) unlink("fifo")
        // parintele deja a deschis fifo-ul, si a si scris in el
        // apelul 'read' este blocant pentru copil, astfel ca nu poate disparea fifo-ul fara sa se fi citit din el
        // unlink("fifo") aici va da eroare cu EBUSY, fifo-ul fiind folosit de parinte
        exit(0);
    }

    f = open("fifo", O_WRONLY);
    // scrie 2 caractere -> "xy"
    write(f, "xy", 2);
    close(f);

    wait(NULL);
    unlink("fifo");
    return 0;
}