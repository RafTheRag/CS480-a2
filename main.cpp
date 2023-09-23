#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include "shared.h"
#include "readvocab.h"
#include "readlines.h"
#include "countvocabstrings.h"

using namespace std;

int main(int argc, char** argv) {
    int option;

    SHARED_DATA *sharedData = new SHARED_DATA();
    ifstream testIn(argv[2]);
    ifstream vocabIn(argv[1]);
    
    /*Contains the code for optional arguements for command line
    */
    // while ((option = getopt(argc, argv, "p:m:v:")) != -1) {
    //     switch (option) {
    //         case 'p':
    //             //converts to int
    //             sharedData->numOfProgressMarks = atoi(optarg);
    //             break;
    //         case 'm':
    //             sharedData->hashmarkInterval = atoi(optarg);
    //             break;
    //         case 'v':
    //             sharedData->minNumOfVocabStringsContainedForPrinting = atoi(optarg);
    //             break;
    //         default:
    //             cerr << "Usage: " << argv[0] << "vocabulary.txt testfile.txt [-p progressMarks] [-m hashmarkInterval] [-v minNumOfVocabStrings]" << endl;
    //             exit(EXIT_FAILURE);
    //     }
    // }



}