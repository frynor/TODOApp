#!/bin/bash

source="/home/frynor/workspace/TODOApp/TODO"
dest="/home/frynor/workspace/TODOApp/DONE"

mkdir -p "$dest"

# Use a simple for loop to iterate over files
for file in "$source"/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        destfile="$dest/$filename"
        
        if [ -e "$destfile" ]; then
            if [ "$file" -nt "$destfile" ]; then
                echo "Newer file detected, copying: $filename"
                cp "$file" "$destfile"
            else
                echo "File exists and is not newer, skipping: $filename"
            fi
        else
            echo "Copying new file: $filename"
            cp "$file" "$destfile"
        fi
    fi
done

echo "Transfer complete."
