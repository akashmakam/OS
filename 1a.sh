#!/bin/bash
read -p "Enter a number: " num
rnum=0
onum=$num
while [ $num -ne 0 ]; do
    rnum=$((rnum*10 + num%10))
    num=$((num / 10))
done
if [ $rnum -eq $onum ]; then
    echo -e "\nThe input number is a palindrome."
else
    echo -e "\nThe input number is not a palindrome."
fi