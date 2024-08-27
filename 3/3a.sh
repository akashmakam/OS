# Largest of n numbers in an array
#!/bin/bash
read -p "Enter the size of the array: " n
echo -e "\nEnter the numbers:"
declare -a array
read -a array
largest=${array[0]}
for ((i=1; i < n; i++)); do
    if [ ${array[i]} -gt $largest ]; then
        largest=${array[i]}
    fi 
done
echo -e "\nThe largest of the $n numbers is $largest."