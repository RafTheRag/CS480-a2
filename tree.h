/*
 *@Author: Rafael Ramirez
 *REDID: 825477088
*/

#ifndef TREE_H
#define TREE_H
#define LENGTH 31

#include <string.h>

//Declare the CharNode class with 31 child nodes for the 31 valid characters.
class CharNode {
public:
    CharNode *child[LENGTH];

    CharNode();

};

//Declare the CharTrie class with 3 oublic methods and a private root of type CharNode.
class CharTrie {
public:
    CharTrie();

    ~CharTrie();

    int getIndex(char n);

    bool insert(const char *strBeingInserted);

    bool search(const char *strBeingSearched);

    void nodeDelete(CharNode *root);

private:
    CharNode *root;
};

#endif // TREE_H