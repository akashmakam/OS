# Prime numbers in specified range
#!/bin/bash
echo "Enter the range:"
read -p "Lowerbound: " n1
read -p "Upperbound: " n2
echo -e "\nThe prime numbers in the range $n1 to $n2 are:"
for ((p=n1; p<=n2; p++)) do
    flag=0
    for ((i=2; i<=(p/2); i++)) do
        if [ $((p%i)) -eq 0 ]; then
            flag=1
            break
        fi
    done
    if [ $flag -eq 0 ]; then
        echo "$p"
    fi
done