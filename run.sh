#!/bin/bash

FILES_DIR="files/"
OUTPUT_DIR="output/"

while getopts ":cdl:i:o:" opt; do
  case $opt in
    c) 
        mode="encode"
        ;;
    d) 
        mode="decode"
        ;;
    l) 
        dictionary_file="$OPTARG"
        ;;
    i) 
        input_file="$OPTARG"
        ;;
    o) 
        output_file="$OPTARG"
        ;;
    \?) 
        echo "Invalid option -$OPTARG" >&2
        exit 1
        ;;
  esac
done

if [ -z "$dictionary_file" ] || [ -z "$input_file" ] || [ -z "$output_file" ]; then
    exit 1
fi

dictionary_file="$FILES_DIR$dictionary_file"
input_file="$FILES_DIR$input_file"
output_file="$OUTPUT_DIR$output_file"


files=( "$input_file" "$dictionary_file" )
for file in "${files[@]}"
do
    encoding="$(file -bi $file | awk '{print $2;}' | cut -d'=' -f2)"
    if [ $encoding != "iso-8859-1" ]; then
        iconv -c -f UTF-8 -t ISO8859-1 "$file" > "${file}.new"
        mv -f "${file}.new" "$file"
    fi
done

echo "#🔥🔥🔥 PERFORMANCE INFORMATION 🔥🔥🔥" >> "$OUTPUT_DIR"/performance-information.md

if [ "$mode" == "encode" ]; then
    echo "##RUN TIME (Encoding)  " >> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`" >> "$OUTPUT_DIR"/performance-information.md
    (/usr/bin/time -f "Execution time: %E  " ./app \
        -c -l="$dictionary_file" -i="$input_file" -o="$output_file") 2>> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`  " >> "$OUTPUT_DIR"/performance-information.md
    echo "##MEMORY FOOTPRINT (Encoding)  " >> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`" >> output/performance-information.md
    valgrind ./app -c -l="$dictionary_file" -i="$input_file" -o="$output_file" 2>> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`" >> "$OUTPUT_DIR"/performance-information.md
else  
    echo "##RUN TIME (Decoding)  " >> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`" >> "$OUTPUT_DIR"/performance-information.md
    (/usr/bin/time -f "Execution time: %E  " ./app \
        -d -l="$dictionary_file" -i="$input_file" -o="$output_file") 2>> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`  " >> "$OUTPUT_DIR"/performance-information.md
    echo "##MEMORY FOOTPRINT (Decoding)  " >> "$OUTPUT_DIR"/performance-information.md
    echo "\`\`\`" >> "$OUTPUT_DIR"/performance-information.md
    valgrind ./app -d -l="$dictionary_file" -i="$input_file" -o="$output_file" 2>> "$OUTPUT_DIR"/performance-information.md 
    echo "\`\`\`" >> "$OUTPUT_DIR"/performance-information.md
fi

pandoc -f markdown "$OUTPUT_DIR"/performance-information.md > "$OUTPUT_DIR"/performance-information.html
rm "$OUTPUT_DIR"/performance-information.md