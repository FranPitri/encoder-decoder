#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Trie/TrieNode.h"


int main(int argc, char* argv[]){

	TrieNode* head = new TrieNode();

    std::cout << "Working with file.." << '\n';

    std::ifstream infile("isotest.txt");

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string key, mirror;
        if (!(iss >> key >> mirror)) { break; } // error
        head->insert(key, mirror);
    }
  
    std::cout << "Finished working with file.." << '\n';
    

    std::cout << "Started encoding.." << '\n';
    
    std::ifstream phrase_infile("books/iso-game-of-thrones.txt");

    std::string phrase_line;
    std::string result;
    while (std::getline(phrase_infile, phrase_line)) {
        
        std::string word;
        for (unsigned char letter : phrase_line) {
            if (letter != ' ') {
                word += convert(letter);
            } else {
                try {
                    //for (auto &letter : word)
                    //    std::tolower(letter);
                    result += head->search(word) + ' ';
                    //std::cout<<word << '\n';
                } catch (...) {
                    result += word + ' ';
                }
                word = "";
            }
        }
        try {
            //for (auto &letter : word)
            //    std::tolower(letter);
            //result += head->search(word) + ' ';
        } catch (...) {
            result += word + ' ';
        }
        
    }

    std::ofstream outfile("out.txt");

    outfile << result;

    outfile.close();

    std::cout << "Finished encoding.." << '\n';
    
	return 0;
}




