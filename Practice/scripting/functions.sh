
Min() {
    if [[ $1 -lt $2 ]];
    then
        echo "$1 is smaller than $2"
    elif [[ $1 -gt $2 ]];
    then 
        echo "$1 is larger than $2"
    else
        echo "$1 is equal to $2"
    fi
}

read -p "Enter two numbers separated by space: " N1 N2
Min $N1 $N2
