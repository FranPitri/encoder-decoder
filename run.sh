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

echo "#🔥🔥🔥 PERFORMANCE INFORMATION 🔥🔥🔥" >> output/performance-information.md

if ["$mode" == "encode"]; then
    echo "##RUN TIME (Encoding)" >> output/performance-information.md
    echo "\`\`\`" >> output/performance-information.md
    (/usr/bin/time -f "Execution time: %E" ./app \
        -c -l "$dictionary" -i "$input_file" -o "$output_file") 2>> output/performance-information.md
    echo "\`\`\`\n" >> output/performance-information.md
    echo "##MEMORY FOOTPRINT (Encoding)" >> output/performance-information.md
    echo "\`\`\`" >> output/performance-information.md
    valgrind ./app -c -l "$dictionary" -i "$input_file" -o "$output_file" 2>> output/performance-information.md
    echo "\`\`\`\n" >> output/performance-information.md
else  
    echo "##RUN TIME (Decoding)" >> output/performance-information.md
    echo "\`\`\`" >> output/performance-information.md
    (/usr/bin/time -f "Execution time: %E" ./app \
        -d -l "$dictionary" -i "$input_file" -o "$output_file") 2> output/execution-time.txt
    echo "\`\`\`\n" >> output/performance-information.md
    echo "##MEMORY FOOTPRINT (Encoding)" >> output/performance-information.md
    echo "\`\`\`" >> output/performance-information.md
    valgrind ./app -d -l "$dictionary" -i "$input_file" -o "$output_file" 2>> output/performance-information.md 
    echo "\`\`\`\n" >> output/performance-information.md
fi

pandoc -f markdown output/performance-information.md > output/performance-information.html
rm output/performance-information.md