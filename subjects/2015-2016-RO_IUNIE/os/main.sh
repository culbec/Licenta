#!/bin/bash

#* i va lua fiecare token din fisierul $1, delimitate dupa whitespaces
#* cut -c1: va selecta primul caracter de pe token $i
#*      daca $i reprezinta un token cu un singur numar, atunci append la $1.nr, salveaza toate numerele
#*      daca c este litera lower/upper, atunci se creeaza un nou fisier cu caracterul, la care se appenduieste token-ul
#*      pentru orice alte tokeni, se aduna la n 1
#* se afiseaza cate tokeni care fie nu sunt numere, fie incep cu caractere care nu sunt litere upper/lower


#* b) daca script-ul este rulat fara argumente, (?eroare?) se blocheaza executia, neavand din ce sa citeasca
#* c) rularea './abc.sh f3' va crea fisierele:
# a -> abc \n aa \n
# b -> b2 \n
# f3.nr -> 74 \n
# se afiseaza 3
#* d) f3
# abc
# bcd
# cdb
# dcd
n=0
for i in `cat $1`; do
    c=`echo $i | cut -c1`
    #* a) match pe liniile care contin doar cifre
    if echo $i | grep -q "^[0-9][0-9]*$"; then
        echo $i >> $1.nr
    elif echo $c | grep -q "[A-Za-z]"; then
        echo $i >> $c
    else
        n=`expr $n + 1`
    fi
done
echo $n