#!/bin/bash
read -p "Enter the size of the array: " n
echo -e "\nEnter the numbers:"
declare -a array
for ((i=0; i < n; i++)); do
    read -p "Enter number $((i+1)): " array[i]
done
largest=${array[0]}
for ((i=1; i < n; i++)); do
    if [ ${array[i]} -gt $largest ]; then
        largest=${array[i]}
    fi 
done
echo -e "\nThe largest of the $n numbers is $largest."