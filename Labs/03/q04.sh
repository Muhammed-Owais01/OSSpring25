#!/bin/bash
echo "Enter file or directory path:"
read path

if [ -f "$path" ]; then
	echo "$path is a regular file."
	echo "File size: $(stat -c %s "$path") bytes"
	echo "Permissions: $(ls -l "$path" | awk '{print $1})"
elif [ -d "$path" ]; then
	echo "$path is a directory"
	echo "Contains $(ls -l "$path" | wc -l) items."
else
	echo "$path does not exist."
fi
