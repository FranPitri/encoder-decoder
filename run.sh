#!/bin/bash

while getopts ":cdl:i:o:" opt; do
  case $opt in
    c) 
        mode="encode"
        ;;
    d) 
        mode="decode"
        ;;
    l) 
        dictionary="$OPTARG"
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

if [-z "$dictionary" || -z "$input_file" || -z "$output_file"]; then
    exit 1
fi

if ["$mode" == "encode"]; then
    (/usr/bin/time -f "Execution time: %E" ./app \
        -c -l "$dictionary" -i "$input_file" -o "$output_file") 2> output/execution-time.txt
    valgrind --log-file="output/memory-usage.txt" ./app \
        -c -l "$dictionary" -i "$input_file" -o "$output_file"
else  
    (/usr/bin/time -f "Execution time: %E" ./app \
        -d -l "$dictionary" -i "$input_file" -o "$output_file") 2> output/execution-time.txt
    valgrind --log-file="output/memory-usage.txt" ./app \
        -d -l "$dictionary" -i "$input_file" -o "$output_file"  
fi