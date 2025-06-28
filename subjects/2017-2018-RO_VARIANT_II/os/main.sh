#!/bin/bash

# citeste input de la stdin sau din fisier, linie cu linie
# verifica daca ce s-a citit incepe cu cifra
# afirmativ, aduna in x ceea ce s-a citit in a
# citeste pana cand avem string-ul vid

# EXECUTIA: cat test | ./a.sh
#* a) Ce se va afisa daca test contine numere de la 0 la 5 pe linii consecutive?
# 15

#* b) Ce se va afisa daca test contine numere de la 0 la 5 pe aceeasi linie, separate prin spatiu
# Eroare: a se va evalua la "0 1 2 3 4 5", expr va incerca sa faca "0 1 2 3 4 5" + 0, care nu va putea fi interpretat ca numar (string-ul a)

#* c) Ce se va afisa daca in fisierul test la punctul (a) se adauga o linie cu secventa abc?
# 15, nu va face match grep

#* d) Ce se va afisa daca in fisierul test de la punctul (a) se adauga o linie cu secventa 6bc?
# Eroare:...
# string vid
read a
x=0
while [ "$a" != "" ]; do
    if echo "$a" | grep -q "^[0-9].*$"
    then
        x=`expr $a + $x`
    fi
    read a
done
echo $x