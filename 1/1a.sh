# Palindrome Checker
#!/bin/bash

read -p "Enter a number to determine whether it is a palindrome or not: " num

# Approach 1: Using the 'rev' command (string-based method)
rnum=$(echo "$num" | rev)

if [ "$num" = "$rnum" ]; then
    echo -e "\nThe input number is a palindrome! (Approach 1)"
else
    echo -e "\nThe input number is not a palindrome! (Approach 1)"
fi

# Approach 2: Using arithmetic operations (numeric-based method)
rnum=0
onum=$num

while [ $num -ne 0 ]; do
    rnum=$((rnum * 10 + num % 10))
    num=$((num / 10))
done

if [ "$onum" -eq "$rnum" ]; then
    echo -e "\nThe input number is a palindrome! (Approach 2)"
else
    echo -e "\nThe input number is not a palindrome! (Approach 2)"
fi