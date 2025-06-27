#!/bin/bash

#* VA PRIMI ARGUMENTE DE FORMA: director text director text ...
#* VA DA SKIP LA COMBINATII CARE NU SUNT director text PANA PRIMESTE O ASTFEL DE COMBINATIE

# a) explicat in comentarii
# b) explicat in comentarii
# c) daca linia 9: sed "s/^$2//" $F > $F.text va fi inlocuita cu sed `s/^$2//` $F > $F.text
# atunci executia va da eroare la acea linie, deoarece interpretorul shell va incerca sa proceseze `s/^$2//` ca o comanda
# care are mari sanse sa nu existe; s-ar incerca sa se execute comanda sed care va fi rezultatul `s/^$2//`, care s-ar putea cel mai probabil sa nu existe
# d) daca se sterg liniile 13 si 14: else\nshift, atunci argumentele care nu sunt directoare nu vor mai fi eliminate, astfel fiind un loop continuu daca 
# exista un astfel de argument primit in linia de comanda

# verifica daca $1 (primul argument din linia de comanda) nu este string vid
# -z "$1" ar fi verificat daca $1 este string vid
while [ -n "$1" ]; do
    # verifica daca $1 este un fisier de tip director
    if [ -d $1 ]; then
        # find va cauta recursiv in directorul $1 cautand fisiere obisnuite (flag f)
        for F in `find $1 -type f`; do
            # determina daca fisierul F este de tip text
            if file $F | grep -q -v text; then
                # va fi eroare daca fisierul nu este de tip text
                # si va procesa urmatorul fisier
                echo "Eroare: $F"
                continue
            fi

            # in liniile in care apare al doilea argument ca inceput de linie, acesta va fi inlocuit cu ''
            sed `s/^$2//` $F > $F.text
        done
        # muta argumentele din linia de comanda cu o pozitie la stanga
        shift
        # muta argumentele din linia de comanda cu o pozitie la stanga
        shift
        # $1 <- $3, $2 <- $4...
    else
        # daca nu e director, muta argumentele din linia de comanda cu o pozitie la stanga
        shift
        # $1 <- $2, $2 <- $3...
    fi
done