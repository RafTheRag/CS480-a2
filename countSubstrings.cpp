/*
 *@Author: Rafael Ramirez
 *REDID: 825477088
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <string.h>
#include "tree.h"

int main(int argc, char **argv){

    //Here I have a vector of strings to store the incoming test words to be inserted in the trie.
    std::vector<std::string> testWords;
    std::ifstream testIn(argv[2]);
    std::string testLine;

    //here it reads through each line making it all lowercase letters and pushing it to the testWords vector.
    while(std::getline(testIn, testLine)){

        std::transform(testLine.begin(), testLine.end(), testLine.begin(), ::tolower);
        testWords.push_back(testLine);
    }

    //Similar to the previous vector but here we store strings that will be seearched for in the trie.
    std::vector<std::string> vocabWords;
    std::ifstream vocabIn(argv[1]);
    std::string vocabLine;

    //Same as before read in all the lines, turn them to lowercase letters and push to vocabWords vector.
    while(std::getline(vocabIn, vocabLine)){

        std::transform(vocabLine.begin(), vocabLine.end(), vocabLine.begin(), ::tolower);
        vocabWords.push_back(vocabLine);
    }

    //here we iterate for each value s in testWords making a substring counter and a new trie for every individual word and its prefixes in testWords.
    for(auto &s: testWords){

        int subStrCount = 0;

        CharTrie charTrie;
        charTrie.insert(s.c_str()); //The current string is inserted as a c string to comply with the const *char requirements of the insert emthod.

        //In this nested for each loop we search through our current testWords string's trie for each string t found in vocabWords.
        for(auto &t: vocabWords){

            if(charTrie.search(t.c_str())){

                subStrCount++; //If our current string in vocabWords is found in the trie of the current string in testWords wet increment our substring counter by 1
            }
        
        }

        std::cout << subStrCount << std::endl; //here we output the amount of substrings found in each of the testWords string's tries.
    }
}