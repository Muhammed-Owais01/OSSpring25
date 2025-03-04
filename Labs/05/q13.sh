#!/bin/bash
read -p "Enter a filename: " file
if [[ -f "$file" ]]
then
	count=$(wc -l < "$file")
	echo "File has $count lines"
else
	echo "File could not be found"
fi
