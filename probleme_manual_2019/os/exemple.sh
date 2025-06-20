#!/usr/bin/sh

#* E1: Scrieti in fisierul a.txt toate procesele din sistem cu detalii, inlcouid toate secventele de unul sau mai multe spatii cu un singur spatiu
ps -ef | sed "s/ \+/ /g" >a.txt

#* E2: Afisati utilizatorii ultimelor 7 procese din fisierul a.txt (creat la E1), sortati alfabetic
# Nu am creat a.txt, lucram direct cu comanda de mai sus
ps -ef | sed "s/ \+/ /g" | tail -n 7 | cut -d' ' -f1 | sort

#* E3. Scrieti in fisierul b.txt toate liniile din fisierul a.txt (creat in exemplul E1) cu exceptia primei linii.
# head/tail -n +NUM da skip la coada/cap ultimelor/primelor NUM-1 linii
tail -n +2 a.txt >b.txt

#* E4. Afisati utilizatorii proceselor din fisierul b.txt, eliminand duplicatele
cut -d' ' -f1 b.txt | uniq

#* E5. Afisati primii 3 utilizatori cu cele mai multe procese din fisierul b.txt, ordonati descendent dupa numarul de procese.
# Luam utilizatorii, sortam dupa nume, vedem cate aparitii au in stream, sortam iar numeric dupa aparitii, reversed, afisam top 3
cut -d' ' -f1 b.txt | sort | uniq -c | sort -n -r | head -n 3

#* E6. Afisati toate liniile din fisierul b.txt care nu incep cu cuvantul root.
ps -ef | sed "s/ \+/ /g" | tail -n +2 | grep -Ev "^root.*"

#* E7. Afisati numarul de linii din fisierul f.txt
cat f.txt | wc -l
wc -l f.txt | sed "s/ .*//"

#* E8. Afisati liniile din fisierul f.txt care contin cuvantul "bash"
grep "bash" f.txt

#* E9. Stergeti liniile din fisierul f.txt care contin cuvantul "bash"
sed "/bash/d" f.txt

#* E10. Afisati liniile din fisierul f.txt inlocuind toate vocalele litere mici in litere mari
sed "y/aeiou/AEIOU" f.txt

#* E11. Afisati liniile din fisierul f.txt duplicand secventele de doua sau mai multe vocale
sed "s/\([aeiouAEIOU]\{2,\}\)/\1\1/g" f.txt

#* E12. Afisati liniile din fisierul f.txt inversand toate perechile de litere
sed "s/\([A-Za-z]\)\([A-Za-z]\)/\2\1/g" f.txt

#* E13. Afisati liniile din fisierul f.txt care contin secvente de 3 pana la 5 cifre pare.
grep "[02468]{3,5}" f.txt

#* E14. Stergeti toate fisierele cu extensia txt din directorul curent, ascunzand iesirea standard si iesirea eroare a comenzii
rm *.txt 2>&1 >&-
rm *.txt 2>&1 >/dev/null
rm *.txt 2>/dev/null 1>/dev/null

#* E15. Afisati numele fisierului si subdirectorului cu cele mai lungi nume din directorul dat ca argument in linia de comanda.
#* Considerati doar fisierele si directoarele care nu sunt ascunse (numele lor nu incepe cu punct).

#!/usr/bin/sh

D=$1

if [! -d $D ]; then
    echo "USAGE: $0 <directory>"
    exit 1
fi

MAX_FILE_LEN=0
MAX_FILENAME=""

MAX_SUBDIR_LEN=0
MAX_SUBDIR=""

for F in `find $D | tail -n +2`; do
    L=`echo $F | wc -c`

    if [ -f $F ]; then
        if [ $L -gt $MAX_FILE_LEN ]; then
            MAX_FILE_LEN=$L
            MAX_FILE_NAME=$F
        fi
    else if [ -d $F ]; then
        if [ $L -gt $MAX_SUBDIR_LEN ]; then
            MAX_SUBDIR_LEN=$L
            MAX_SUBDIR=$F
        fi
    else
        echo "$F is neither a file or a directory!"
    fi
done

echo "File with longest name: $MAX_FILENAME"
echo "Subdirectory with longest name: $MAX_SUBDIR"

#* E16. Afisati primul argument din linia de comanda care este numar pozitiv par.

#!/usr/bin/sh

while [ -n "$1" ]; do
    if echo "$1" | grep -q '^[0-9]*[02468]$'; then
        echo $1
        break
    fi
    shift
done

#* E17. Cititi valori de la intrarea standard pana cand suma tuturor valorilor numar natural este
#*      strict mai mare decat 10. 

#!/usr/bin/sh

sum=0

while [ $sum -le 10 ]; do
    read -p "Value: " k

    if echo $k | grep -q '^[0-9]+$'; then
        sum=`expr $sum + $k`
    fi
done

#* E18. Afisati numele tuturor fisierelor care contin text ASCII dintr-un director dat si toate ierarhia de subdirectoare din el

#!/usr/bin/sh

D=$1

if [ ! -d $D ]; then
    echo "USAGE: $0 <directory"
    exit 1
fi

# fisiere cu encoding ASCII
find $D -type f | while read F; do
    if file $F | grep -q "ASCII"; then
        echo $f
    fi
done

# ierarhia
tree -d $D