# Palindrome Checker
#!/bin/bash
read -p "Enter a number to determine whether it is a palindrome or not: " num
rnum=$(echo "$num" | rev)
if [ "$num" = "$rnum" ]; then
    echo -e "\nThe input number is a palindrome."
else
    echo -e "\nThe input number is not a palindrome."
fi