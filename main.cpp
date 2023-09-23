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
    //             if (sharedData->numOfProgressMarks < 10){
    //                 cerr << "Number of progress marks must be a number and at least 10." << endl;
    //                 exit(EXIT_FAILURE);
    //             }
    //             break;
    //         case 'm':
    //             sharedData->hashmarkInterval = atoi(optarg);
    //             if (sharedData->hashmarkInterval <= 0 || sharedData->hashmarkInterval > 10) {
    //                 cerr << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10." << endl;
    //                 exit(EXIT_FAILURE);
    //             }
    //             break;
    //         case 'v':
    //             sharedData->minNumOfVocabStringsContainedForPrinting = atoi(optarg);
    //             break;
    //         default:
    //             cerr << "Usage: " << argv[0] << "vocabulary.txt testfile.txt [-p progressMarks] [-m hashmarkInterval] [-v minNumOfVocabStrings]" << endl;
    //             exit(EXIT_FAILURE);
    //     }
    // }

    pthread_t readvocabThread;
    pthread_t readlinesThread;
    pthread_t countvocabstringsThread;
    
    sharedData->fileName[0] = argv[1]; //for vocab file
    sharedData->fileName[1] = argv[2]; //for test file

    //??not sure how to pass the files
    if (pthread_create(&readvocabThread, NULL, &readvocab, &sharedData)){
        //error handling
    }

    if (pthread_create(&readlinesThread, NULL, &readlines, &sharedData)){
        //error handling
    }

}