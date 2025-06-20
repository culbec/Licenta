#!/bin/bash

while read X; do
    # da match pe liniile, care:
    #   1. incep cu o secventa de multiple caractere care nu sunt + sau -
    #   2. acea secventa este urmata de + sau - urmate de o secventa de multiple caractere care nu sunt + sau -, de multiple ori
    # exemplu OK: 1 + 2 + 3, ab3+3-qq3
    # exemplu WRONG: -123+33, +ab!-33
    if echo "$X" | grep -E -q '^[^+-]+([+-][^+-]+)+$'; then
        # primul sed inlatura caracterele care nu sunt cifre sau + -
        # al doilea sed pune spatii intre ce urmeaza inaintea lui + - si dupa
        echo "$X" | sed -E "s/[^0-9+-]//g" | sed -E "s/([+-])/ \1 /g"
    fi
# dupa procesare, vom avea linii in stdout care de forma: ceva (+-) ceva (+-) ceva ...
# read citeste linie cu linie, separand tokenii prin spatii sau tab
# variabilele pe care le primeste read sunt pozitionali si sunt asignati fiecarui token
# daca avem mai putine variabile decat tokeni, the last takes the rest
done < a.txt | while read A B C; do
    # 1. xx2x+x4xx      => grep match => #1 sed: 2+4        => #2 sed: 2 + 4        ==> 6
    # 2. 2 + 1 0 * 3    => grep match => #1 sed: 2 + 103    => #2 sed: 2  +  103    ==> 105
    # 3. 2 + 4 - 5      => grep match => #1 sed: 2 + 4 - 5  => #2 sed: 2  +  4  - 5 ==> 1 
    expr $A $B $C
done

#! daca a.txt nu are newline at the end, atunci ultima linie va fi skipped! (read citeste pana la newline)
#! exemplu:
#!  xx2x+x4xx
#!  2 + 1 0 * 3
#!  2 + 4 - 5 (NO NEW LINE) ==> xx2x+x4xx si 2 + 1 0 * 3