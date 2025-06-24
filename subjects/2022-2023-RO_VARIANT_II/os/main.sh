#!/bin/bash

# $* si $@ fara "" - lista de argumente
# "$*" - argumentele ca un singur string
# "$@" - argumentele ca string-uri separate

# A ia argumentele din linia de comanda
for A in $*; do
    # F ia path-urile fisierelor din directorul x
    for F in x/*; do
        # TRUE daca nu exista linii care sa contina <arg>_+<arg>_+...
        # Exemplu: 5_5___5
        # Doar pentru acelasi argument separat de unul sau mai multe _, consecutiv!
        # Daca apare un alt tip de argument, nu mai face match
        if ! grep -E -q "^$A(_+$A)*$" $F; then
            # introduce argumentul in fisier
            echo "$A" >> $F
        # Daca exista multiple linii care contin acea combinatie a argumentului
        elif [ `grep -E "^$A(_+$A)*$" $F | wc -l` -gt 1 ]; then
            # elimina toate liniile unde ar aparea acel argument
            grep -E -v "^$A(_{1,}$A){0,}$" $F > $F.aux
            # adauga argumentul in fisier
            echo "$A" >> $F.aux
            # rescrie fisierul
            mv $F.aux $F
        fi
    done
done

# a) x/a.txt:
# abc
# def
# RESULT for 'abc':
# abc
# def

# b) x/b.txt:
# abc
# def
# abc
# RESULT for 'abc':
# def
# abc

# c) x/c.txt:
# def_def
# abc
# abc_def
# abc_abc
# def_def_def
# RESULT for 'abc def'
# * for 'abc':
# def_def
# abc_def
# def_def_def
# abc
# * for 'def':
# abc_def
# abc
# def