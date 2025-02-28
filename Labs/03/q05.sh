#!/bin/bash
if [ $# -ne 1 ]; then
	echo "Usage: $0 <directory_path>"
	exit 1
fi

src_dir="$1"
backup_dir="$HOME/backup_$(date +%Y-%m-%d_%H-%M-%S)"

if [ ! -d "$src_dir" ]; then
	echo "Error: Directory does not exist"
	exit 1
fi

mkdir -p "$backup_dir"
cp -r "$src_dir"/* "$backup_dir"
file_count=$(find "$backup_dir" -type f | wc -l)
dir_count=$(find "$backup_dir" -type d | wc -l)

echo "Backup completed"
echo "Backup location: $backup_dir"
echo "Files backed up: $file_count"
echo "Directories backed up: $dir_count"
