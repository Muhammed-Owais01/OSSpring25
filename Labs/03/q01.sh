if [ $# -ne 2 ]; then
	echo "Usage: $0 num1 num2"
	exit 1
fi
result=$(( $1 * $2 ))
echo "Multiplication of $1 and $2 is $result"
