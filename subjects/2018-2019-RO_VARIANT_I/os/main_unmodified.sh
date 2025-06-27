#!/bin/bash
for F in *.sh; do
    A=`grep "^[ \t]*[^ \t#]" $F | wc -l`
    B=`wc -l < $F`
    if [ $A -lt `expr $B - $A` ]; then
        echo $F
    fi
done