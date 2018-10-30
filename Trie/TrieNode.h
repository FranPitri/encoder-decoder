#include <iostream>
#include "../HashMap/HashMap.h"
#include "../HashMap/hashFunction.h"

#ifndef TRIENODE_H
#define TRIENODE_H
//#define int ALPHABET_EXTENDED = 33;

#include <string>

class TrieNode { 
    bool isLeaf;
    std::string mirror;
	HashMap<unsigned char, TrieNode*> *children; 

    public:
        
        TrieNode() {
            this->isLeaf = false;
			children = new HashMap<unsigned char, TrieNode*>(34, convert);
        }

        void insert(std::string, std::string);
        std::string search(std::string);

};

void TrieNode::insert(std::string key, std::string mirror) {
	// start from root node
	TrieNode* current = this;
	for (int i = 0; i < key.length(); i++) {
		unsigned char unsigned_k = key[i];
		char k = key[i];
		// create a new node if path doesn't exist
		if (current->children->get((unsigned char)key[i]) == nullptr)
			current->children->put((unsigned char)key[i], new TrieNode());

		// go to next node
		current = current->children->get((unsigned char)key[i]);
	}

	// mark current node as leaf
	current->isLeaf = true;
    current->mirror = mirror;
}

std::string TrieNode::search(std::string key) {
	// throw if Trie is empty
	if (this == nullptr)
		throw "Not found";

	TrieNode* current = this;
	for (int i = 0; i < key.length(); i++) {
		unsigned char unsigned_k = key[i];
		char k = key[i];
		// go to next node
		current = current->children->get((unsigned char)key[i]);

		// if string is invalid (reached end of path in Trie)
		if (current == nullptr)
			throw "Not found";
	}

	// if current node is a leaf and we have reached the
	// end of the string, return mirror
	if (current->isLeaf)
        return current->mirror;
    else
        throw "Not found";
}


#endif