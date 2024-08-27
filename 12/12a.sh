# Largest of three numbers
#!/bin/bash
n=3
echo "Enter the three numbers:"
declare -a array
read -a array
largest=${array[0]}
for ((i=1; i < n; i++)); do
    if [ ${array[i]} -gt $largest ]; then
        largest=${array[i]}
    fi 
done
echo -e "\nThe largest of the three numbers is $largest."