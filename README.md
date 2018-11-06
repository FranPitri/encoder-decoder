# ｅｎｃｏｄｅｉｔｄｅｃｏｄｅｉｔ

A little c++ script wich encodes/decodes input based on a dictionary.

Its only purpose is to be as 🔥 **BLAZING FAST** 🔥 as possible.

Made with ❤ for the Algorithms & Data Structures course at UCC.

## Usage

To run it, simply use these commands

```bash
docker build -t encoder-decoder .
```
```bash
docker run --rm -v {files_dir}:/app/files -v $(pwd):/app/output/ encoder-decoder \
    [-d/-c] -i {input_filename} -o {output_filename} -l {dictionary_file}    
```

This will run the script and leave behind an html file with some performance information in the directory you ran it.
