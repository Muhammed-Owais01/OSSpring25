read -p "Enter the number of directories to be created: " numDir

# while [[ numDir -gt 0 ]] 
# do
#     read -p "Enter the name of directory: " dirName
#     mkdir $dirName
#     if [[ $? = 1 ]];
#     then
#         echo "Directory creation failed"
#     fi
#     (( numDir-- ))
# done

for (( i=1; i <= numDir; i++ ))
do
    read -p "Enter the name of directory: " dirName
    mkdir $dirName
    if [[ $? = 1 ]];
    then
        echo "Directory creation failed"
    fi
done