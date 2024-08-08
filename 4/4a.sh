# Matrix addition
#!/bin/bash
declare -A a
declare -A b
read -p "Enter the row size of the matrices: " m
read -p "Enter the column size of the matrices: " n
echo -e "\nEnter the elements of the first matrix:"
for ((i=0; i < m; i++)) do
    for ((j=0; j < n; j++)) do
        read -p "A[$i,$j]: " a[$i,$j]
    done
done
echo -e "\nEnter the elements of the second matrix:"
for ((i=0; i < m; i++)) do
    for ((j=0; j < n; j++)) do
        read -p "B[$i,$j]: " b[$i,$j]
    done
done
echo -e "\nMatrix A:"
for ((i=0; i < m; i++)) do
    for ((j=0; j < n; j++)) do
        printf "${a[$i,$j]}\t"
    done
    echo ""
done
echo -e "\nMatrix B:"
for ((i=0; i < m; i++)) do
    for ((j=0; j < n; j++)) do
         printf "${b[$i,$j]}\t"
    done
    echo ""
done
echo -e "\nThe sum of the two matrices are:"
for ((i=0; i < m; i++)) do
    for ((j=0; j < n; j++)) do
        sum=$(( ${a[$i,$j]} + ${b[$i,$j]} ))
        printf "%-5s" "$sum"
    done
    echo ""
done