#!/bin/bash
read -p "Enter the number of fibonacci numbers to be generated:" n
a=0
b=1
if [ $n -gt 2 ]; then
    echo "The first $n fibonacci numbers are:"
    echo "$a"
    echo "$b"
    for ((i=2; i<n; i++)) do
        c=$((a+b))
        echo "$c"
        a=$b
        b=$c
    done
else
    echo "Enter a number greater than 2."
fi