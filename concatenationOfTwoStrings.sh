# Shell script to concatenate two strings
#!/bin/bash
echo "Program to concatenate two strings!"
echo "Enter the first string:"
read str1
echo "Enter the second string:"
read str2
result="${str1} ${str2}"
echo "$result"