#!/bin/bash
echo "Enter a filename:"
read filename
if [ ! -f "$filename" ]; then
	echo "File does not exist"
	exit 1
fi
echo "$(date)" >> "$filename"
echo "Current date and time appended to $filename"
