# Shell script to generate prime numbers within a given range.

#!/bin/bash

echo -e "\nEnter the range in which the prime numbers should be generated:"
read -p "Lower bound: " lb
read -p "Upper bound: " ub

echo -e "\nThe prime numbers in range are:"
for ((i=lb; i<=ub; i++)); do
    num=$i
    flag=0
    for ((j=2; j*j<=num; j++)); do
        if [ $((num%j)) -eq 0 ]; then
            flag=1
            break
        fi
    done
    if [ $flag -eq 0 ]; then
        echo "$i"
    fi
done