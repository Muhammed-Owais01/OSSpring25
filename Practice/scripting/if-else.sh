read -p "Enter num 1: " num1
read -p "Enter num 2: " num2

if [[ $num1 -lt $num2 ]];
then
    echo "$num1 is smaller than $num2"
elif [[ $num1 -gt $num2 ]];
then
    echo "$num1 is greater than $num2"
else
    echo "$num1 is equal to $num2"
fi

read -p "Enter y(yes) or n(no): " YN
if [[ "x$YN" = "xy" || "x$YN" = "xY" ]];
then
    echo "You specified yes"
else
    echo "You did not specify yes"
fi