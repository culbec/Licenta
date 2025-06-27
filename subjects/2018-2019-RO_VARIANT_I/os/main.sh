#!/bin/bash

#* a) REZULTAT: numara toate liniile din shell scripts care fie nu sunt comentarii, fie nu sunt shbangs
#*           fie sunt de forma [' '\t]*<ceva>#, cumva comenzi shell urmate imediat de comentarii sau ceva
#* DETERMINA NUMELE FISIERELOR SHELL CARE AU MAI PUTINE LINII DE COMENTARII + SHBANGS DECAT RESTUL LINIILOR
#* b) Nu se va afisa nimic: numarul liniilor match-uite, salvate in variabila A, este 7, iar B are 8, astfel 7 nu e mai mic decat 1
#* c) regex-ul e explicat in comms
for F in *.sh; do
    # grep face match pe liniile care incep cu ' ' sau tab (\t) ~de oricate ori~
    # urmate, de un caracter care nu este ' ', tab sau #
    # exemplu: \t\t\t\tf#, va face match \t\t\t\tf
    # numara apoi liniile care au astfel de pattern in ele
    A=`grep "^[ \t]*[^ \t#]" $F | wc -l`

    # numara toate liniile din fisier
    B=`wc -l < $F`

    # daca numarul liniilor care match-uiesc pattern-ul este mai mic
    # decat numarul total de linii din fisier, se face echo la fisier
    if [ $A -lt `expr $B - $A` ]; then
        echo $F
    fi
done