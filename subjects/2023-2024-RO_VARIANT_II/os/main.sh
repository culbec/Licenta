#!/bin/bash

#* EXPLICATIE RULARE
# Proceseaza primul argument din linia de comanda
# Are rolul de a lua o expresie mai lunga, de exemplu: '5 - 120 + 400 - 300 - 100'
# si sa o proceseze incepand din interior
# daca la un moment dat in procesare L nu mai respecta REGEX-ul, se considera ca expresia este malformata
# se opreste atunci cand L contine un singur numar, precedat si urmat de oricate spatii

#********** REZOLVA EXPRESII IN FORMA POLONEZA **********#

#* a) Ce va afisa executia de mai jos?
#* ./a.sh "+ 1 2"
# 3

#* b) Care vor fi valorile variabilelor A, B si C la fiecare iteratie
#* a ciclului while si care va fi valoarea afisata
#* de executia de mai jos?
#* ./a.sh "+ + 1 2 3"
# 1: A = +  , B = 1 + 2, C = 3
# 2: A = '' , B = 3 + 3, C = ''
# Afisare: 6 (echo $L)

#* c) Care vor fi valorile variabilelor A, B si C la fiecare iteratie
#* a ciclului while si care va fi valoarea afisata
#* de executia de mai jos? Justificati raspunsul.
#* ./a.sh "+ + -1 2 -3 4"; echo  $?
# $? - returncode of the last execute command
# 1: A = +  , B = -1 + 2, C = -3 4
# 2: A = '' , B = 1 + -3, C = 4
# 3: DOESN'T MATCH ---> exit 1
# Afisare: 1 ($echo L)

#* d) Explicati in detaliu functionarea liniilor 17-19.
# Verifica printr-un regex daca s-a ajuns la un numar intreg din toata procesarea, precedat si urmat de oricate spatii

#********** ECHO NORMALIZEAZA INPUT-UL DACA AFISEAZA STRING "$STRING" **********#
# Face word splitting si le separa printr-un singur spatiu

# Determina linii care au '<ceva> <+_sau_-> <numar_intreg> <numar_intreg> <ceva>'
RE='^(.*)([+-]) (-?[0-9]+) (-?[0-9]+)(.*)$'
L="$1"
while true; do
    if echo $L | grep -q -v -E "$RE"; then
        exit 1
    fi

    A=`echo $L | sed -E "s/$RE/\1/"`
    B=`echo $L | sed -E "s/$RE/\3 \2 \4/"`
    C=`echo $L | sed -E "s/$RE/\5/"`
    L="$A `expr $B` $C"

    echo "A='$A' B='$B' C='$C'"
    if echo $L | grep -E -q "^ *-?[0-9]+ *$"; then
        break
    fi
done
echo $L