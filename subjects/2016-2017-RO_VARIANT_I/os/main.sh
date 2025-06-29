#!/bin/bash

#* itereaza peste toate fisierele .txt din directorul curent
#*      daca sunt intr-adevar fisiere text, atunci verifica daca fisierul text contine linii care nu incep cu setul de caracterele
#*      al primului argument din linia de comanda
#*          daca exista astfel de linii, se afiseaza numele fisiereului
#*      daca nu sunt fisiere text, atunci se verifica daca numele fisierului incepe cu primul argument din linia de comanda
#*          daca incepe, atunci se afiseaza numele fisierului

#* FISIERE
# abc.txt, fisier text, cu continutul
# abc
# abb
#
# ubb.txt, fisier text cu continutul
# aaa
# bbb
#
# ab.txt, fisier ZIP, redenumit cu extensia txt

#* a) Ce valori va lua variabila f?
# Numele fisierelor cu extensia .txt din directorul curent, sortate crescator dupa nume

#* b) Ce va afisa rularea comenzii
#* ./a.sh a
# ab.txt
# *ubb.txt*

#* c) Explicati expresiile regulare de pe liniile 3 si 6
# Explicatia este in comentarii cod

#* d) Dati un nume si continut de fisier text, cu trei randuri, pentru care linia 4 se executa la rularea comenzii
#* ./a.sh b
# ceva.txt
# bbb
# bcb
# abc

for f in *.txt; do
    if file $f | grep -q "text"; then
        # linii care incep cu orice caracter care nu este in setul de caractere al primului argument din linia de comanda
        if grep -q "^[^$1]" $f; then
            echo "*"$f"*"
        fi
    # linii care incep cu primul argument din linia de comanda
    elif echo $f | grep -q "^$1"; then
        echo $f
    fi
done