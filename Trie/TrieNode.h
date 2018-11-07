#include "../HashMap/HashMap.h"
#include "../HashMap/hashFunction.h"
#include "../Utils/capitalize.h"

#ifndef TRIENODE_H
#define TRIENODE_H
#define ALPHABET_EXTENDED 34

#include <string>

class TrieNode { 
    bool isLeaf;
    std::string mirror;
	HashMap<unsigned char, TrieNode*> *children; 

    public:
        
        TrieNode() {
            this->isLeaf = false;
			children = new HashMap<unsigned char, TrieNode*>(ALPHABET_EXTENDED, convert);
        }

        void insert(std::string, std::string);
        std::string search(std::string);

};

void TrieNode::insert(std::string key, std::string mirror) {
	// start from root node
	TrieNode* current = this;
	for (auto i = key.begin(), end = key.end(); i != end; i++) {
		// create a new node if path doesn't exist
		if (current->children->get((unsigned char)(*i)) == nullptr)
			current->children->put((unsigned char)(*i), new TrieNode());

		// go to next node
		current = current->children->get((unsigned char)(*i));
	}

	// mark current node as leaf
	current->isLeaf = true;
    current->mirror = mirror;
}

std::string TrieNode::search(std::string key) {
	// throw if Trie is empty
	if (this == nullptr)
		return key;

	TrieNode* current = this;
	for (auto i = key.begin(), end = key.end(); i != end; i++) {
		// go to next node
		current = current->children->get((unsigned char)(*i));

		// if string is invalid (reached end of path in Trie)
		if (current == nullptr)
			return key;
	}

	// if current node is a leaf and we have reached the
	// end of the string, return mirror
	if (current->isLeaf) {
		std::string mirror = current->mirror;
		if (isCaps((unsigned char const)key[0]))
			toCaps(mirror);
		return mirror;
	}
	return key;
}


#endif