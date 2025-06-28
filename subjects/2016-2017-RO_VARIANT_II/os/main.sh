#!/bin/bash

#* a) De cate ori se va afisa "OK"? Justificati raspunsul?
# "OK" va fi afisat atunci cand exista 2 fisiere cu acelasi nume care au tipul de fisier diferit: regular file vs directory
# In majoritatea sistemelor UNIX, nu este permis sa existe un fisier cu acelasi nume
# In concluzie: 0 ori

#* b) Care e valoarea variabilie f?
# String ce contine separate pe linii toate path-urile fisierelor de tip regular file din directorul curent, recursiv
f=`find . -type f`
#* c) Care e valoarea variabilei d?
# String ce contine separate pe linii toate path-urile fisierelor de tip directory din directorul curent, recursiv
d=`find . -type d`

#* d) Care sunt valorile variabilei x?
# Ia pe rand fiecare path stocat in lista f
for x in $f; do
    #* e) Care sunt valorile variabilei y?
    # Ia pe rand fiecare path stocat in lista d
    for y in $d; do
        if [ $x = $y ]; then
            echo "OK"
        fi
    done
done