/*
 *@Author: Rafael Ramirez
 *REDID: 825477088
*/

#include <string.h>
#include "tree.h"

//This is the constructor for the CharNode class which initates all our child nodes as a nullptr.
CharNode::CharNode(){

    for(int i = 0; i < LENGTH; i++){

        child[i] = nullptr;
    }
}

bool CharNode::nodeDelete(){
    for (int i = 0; i < LENGTH; i++) {
        if (child[i] != nullptr) {
            child[i]->nodeDelete();  // Recursively delete children
            delete child[i];         // Delete the child node itself
            child[i] = nullptr;      // Set child pointer to nullptr
        }
    }
    return true;
 }

//This is the constructor for the CharTrie class which creates a new instance of the CharNode class, root. Marking the start of our trie.
CharTrie::CharTrie(){
    
    root = new CharNode();
}

CharTrie::~CharTrie(){
    root->nodeDelete();
}

//This method takes in a char and calculates the index value of our next child node using the alphabet and the valid characters.
int CharTrie::getIndex(char n){

    if(n - 'a' >= 0 && n - 'a' <= 25) return n - 'a';
    if(n == ' ') return 26;
    if(n == '\'') return 27;
    if(n == '-') return 28;
    if(n == '_') return 29;
    if(n == '\0') return 30;

    return -1; //If our char is not one of the above valid characters, we return -1 to signify its invalidness.
}

//This method inserts a string and all of its prefixes. For example when we insert "great" we also insert "reat", "eat", "at", "t".
bool CharTrie::insert(const char *strBeingInserted){

    if(strBeingInserted == nullptr){ //cancels insertion if strBeingInserted is null
        
        return false;
    }

    //Nested for loop is used to iterate through the different prefixes of the word being inserted along with the word itself.
    for(int i = 0; i < strlen(strBeingInserted); i++){

        CharNode *node = root;

        for(int j = i; j < strlen(strBeingInserted); j++){

            int index = getIndex(strBeingInserted[j]);

            //If our character at index j is not valid we skip it.
            if(index == -1){

                continue;
            }

            //If we have a valid index with a chracter not yet in our current nodes children we add it.
            if(node->child[index] == nullptr){

                node->child[index] = new CharNode();
            }

            node = node->child[index];  //Proceed into the child of our current node given the index.
        }

    }

   return true; //We return true when we succesfully insert the word and its prefixes.
}

//This method searches for valid substrings in our inserted string given a differnt string. For example, if we insrted "great" and we seatch for "re" it would return true.
bool CharTrie::search(const char *strBeingSearched){

    CharNode *node = root;

    for(int i = 0; i < strlen(strBeingSearched); i++){

        int index = getIndex(strBeingSearched[i]);

        //If we encounter that our child at a given index is a nullptr or our index is invalid, then the string is not found in the trie
        if(index == -1 || node->child[index] == nullptr){

            return false;
        }

        node = node->child[index]; //Proceed into the child of our current node given the index. This means so far the given string is in the trie.
    }

    return true; //If we succesfully reach the end of the searced string then it means it is found in the trie and we return true.
}

void CharTrie::nodeDelete(CharNode *root){
    if(!root) return;
        
    for(int i = 0; i < LENGTH; i++){

        if(root->child[i] != nullptr){

            nodeDelete(root->child[i]);
        }
    }

    delete root;
 }