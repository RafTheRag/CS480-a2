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

    SHARED_DATA sharedData;
    // ifstream testIn(argv[2]);
    // ifstream vocabIn(argv[1]);
    
    
    /*Contains the code for optional arguements for command line
    * p: number of progress marks (either hyphen or #) for displaying 100% progress of a thread execution, default is 50 if not specified.
    * m: place a hash mark “#” in the progress bar every N characters, default is 1
    * v: print number of contained vocab strings to an output file only it is equal to or greater than N, default is 0 if not specified
    */
    sharedData.fileName[0] = argv[1]; //for vocab file
    sharedData.fileName[1] = argv[2]; //for test file

    int arg;
    while ((option = getopt(argc, argv, "p:m:v:")) != -1) {
        switch (option) {
            case 'p':
                //converts to int
                sharedData.numOfProgressMarks = atoi(optarg);
                // if (sharedData.numOfProgressMarks < 10){
                //     cerr << "Number of progress marks must be a number and at least 10." << endl;
                //     exit(EXIT_FAILURE);
                // }
                break;
            case 'm':
                sharedData.hashmarkInterval = atoi(optarg);
                // if (sharedData.hashmarkInterval <= 0 || sharedData.hashmarkInterval > 10) {
                //     cerr << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10." << endl;
                //     exit(EXIT_FAILURE);
                // }
                break;
            case 'v':
                sharedData.minNumOfVocabStringsContainedForPrinting = atoi(optarg);
                break;
            default:
                cout << "Usage: " << argv[0] << " vocabulary.txt testfile.txt [-p progressMarks] [-m hashmarkInterval] [-v minNumOfVocabStrings]" << endl;
                exit(1);
        }
    }

    cout << sharedData.minNumOfVocabStringsContainedForPrinting;
    

    pthread_t readvocabThread;
    pthread_t readlinesThread;
    pthread_t countvocabstringsThread;

    
    //pthread_mutex_init

    

    

    //??not sure how to pass the files
    if (pthread_create(&readvocabThread, NULL, &readvocab, (void*)&sharedData)){
        //error handling
    }

    if (pthread_create(&readlinesThread, NULL, &readlines, (void*)&sharedData)){
        //error handling
    }

    
    pthread_create(&countvocabstringsThread, NULL, &countvocabstrings, (void*)&sharedData);

    pthread_join(readvocabThread, NULL);
    pthread_join(readlinesThread, NULL);
    pthread_join(countvocabstringsThread, NULL);
    
}  