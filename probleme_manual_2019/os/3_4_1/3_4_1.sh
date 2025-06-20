#!/usr/bin/sh

# daca exista fisiere .txt in folderul curent => se va itera peste toate fisierel
# daca nu exista fisiere .txt in folderul curent => atunci for-ul va itera peste argumentele de dupa 
#                                                   'in', care vor fi tratate ca un singur string $IFS separated (space or tab)
#! or should happen?
#! am rulat script-ul cu mai multe fisiere si F ramane tot *.txt, ar trebui folosit find si iterat peste lista aia
#! altfel, F va ramane *.txt si va primi eroare
for F in *.txt; do
    K=`grep abc $F` # EROARE: daca nu exista fisiere .txt
    if [ "$K" != "" ]; then
        echo $F # \*.txt daca exista *.txt si daca acesta contine linii cu 'abc'
    fi
done