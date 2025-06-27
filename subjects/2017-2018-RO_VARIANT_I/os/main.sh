#!/bin/bash
for F in *.c *.cpp *.h; do
    if [ -f $F ]; then
        grep "#include.*<" $F | sed "s/^.*<\(.*\)>.+$/\1/"
    fi
done | sort

# grep ia liniile care au includeri de librarii, dar nu neaparat valide, exemplu
#* #include <stdio.h>
#* #include <stdlib.h>
#* for #include <string i++
# sed inlocuieste de pe liniile match-uite tot include-ul doar cu numele librariei, exemplu
#* #include <stdio.h> ----> stdio.h
#* #include <vector> -----> vector
#* for #include <string i++ ----> for #include <string i++
# la final se sorteaza lexicografic/alfabetic numele librariilor si se afiseaza la stdout
#exemplu:
# for #include <string i++
# #include <fcntl.h>
# #include <stdio.h>
# #include <stdlib.h>
# #include <sys/stat.h>
# #include <sys/types.h>
# #include <unistd.h>