# Shell script to determine the maximum of three numbers
echo "Enter the first number:"
read a
echo "Enter the second number:"
read b
echo "Enter the third number:"
read c
if [ "$a" -gt "$b" ] && [ "$a" -gt "$c" ]; then
    echo "a is greater!"
elif [ "$b" -gt "$a" ] && [ "$b" -gt "$c" ]; then
    echo "b is greater!"
else
    echo "c is greater!"
fi