#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Trie/TrieNode.h"
#include "Utils/characterRange.h"
#include "Utils/cmd.h"

int main(int argc, char* argv[]){

	TrieNode* head = new TrieNode();

    std::string INPUT_FILE = getCmdOption(argc, argv, "-i=");
    std::string OUTPUT_FILE = getCmdOption(argc, argv, "-o=");
    std::string DICTIONARY_FILE = getCmdOption(argc, argv, "-l=");
    
    // Dictionary input stream
    std::ifstream dictionary_infile(DICTIONARY_FILE);

    if (getCmdFlag(argc, argv, "-c")) {
        // Read dictionary (Encode mode)
        std::string dictionary_line;
        while (std::getline(dictionary_infile, dictionary_line)) {
            std::istringstream iss(dictionary_line);
            std::string key, mirror;
            if (!(iss >> key >> mirror)) { break; } // error
            head->insert(key, mirror);
        }
    } else {
        // Read dictionary (Decode mode)
        std::string dictionary_line;
        while (std::getline(dictionary_infile, dictionary_line)) {
            std::istringstream iss(dictionary_line);
            std::string key, mirror;
            if (!(iss >> key >> mirror)) { break; } // error
            head->insert(mirror, key);
        }
    }

    // File to-be-decoded input stream 
    std::ifstream input_infile(INPUT_FILE);

    // File to-be-decoded output stream 
    std::ofstream outfile(OUTPUT_FILE);

    // Read file to be decoded & decode
    std::string in_line;
    while (std::getline(input_infile, in_line)) {
        std::string word;
        for (unsigned char letter : in_line) {
            if (!characterNotSupported(letter)) {
                word += letter;
            } else {
                outfile << head->search(word) << letter;
                word.clear();
            }
        }
        outfile << head->search(word) << '\n';
        word.clear();
    }

    outfile.close();
    
	return 0;
}




