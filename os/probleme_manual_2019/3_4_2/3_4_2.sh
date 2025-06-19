#!/usr/bin/sh

# Fragment de cod ce trebuie adaugat pentru a nu primi eroare pe raport.txt
if [ ! -f raport.txt ]; then touch raport.txt; fi

# ERROR: no such file or directory
more raport.txt
if [ $? -eq 0 ]; then
    rm raport.txt
    touch raport.txt
else
    touch raport.txt
fi

for f in *.sh; do
    if [ ! -x $f ]; then
        chmod +x $f
        echo "$f" >> raport.txt
    fi
done

mail -s "Raport fisiere afectate" admin@scs.ubbcluj.ro <raport.txt
rm raport.txt