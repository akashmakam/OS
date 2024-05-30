# Shell script to find the largest of N numbers (storing numbers in an array)

#!/bin/bash

declare -a array
read -p "Enter the size of the array:" n

largest=0
echo "Enter the elements of the array:"
for ((i=0; i<n; i++)) do
    read -p "Element $((i+1)): " array[i]
    if [ ${array[i]} -ge $largest ]; then
        largest=${array[i]}
    fi
done

echo "The largest number among the entered elements is $largest."