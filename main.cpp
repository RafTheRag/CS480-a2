#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <iostream>
#include "shared.h"
#include "readvocab.h"
#include "readlines.h"
#include "countvocabstrings.h"
#include "display.h"

using namespace std;

void displayProgressBar(double progress) {
    int barWidth = 40;
    int pos = barWidth * progress;

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            std::cout << '-';
        else if (i == pos)
            std::cout << '#';
        else
            std::cout << ' ';
    }
    std::cout << "] " << std::fixed  << progress * 100 << "%\r" << std::flush;
}

void simulateThreadExecution(double (*progressFunc)(), const char* threadName) {
    while (true) {
        double progress = progressFunc();
        if (progress >= 1.0) {
            std::cout << "\n" << threadName << " thread completed." << std::endl;
            break;
        }
        displayProgressBar(progress);
    }

}

double getReadvocabProgress() {
    SHARED_DATA sharedData;
    return (double)sharedData.numOfCharsReadFromVocabFile / (double)sharedData.numOfCharsReadFromVocabFile;
}

double getCountvocabstringsProgress() {
    SHARED_DATA sharedData;
    return (double)(sharedData.numOfProcessedLines) / (double)(sharedData.lineCountInFile[TESTFILEINDEX]);
}

int main(int argc, char** argv) {
    
    if (argc < 3) {
        throw invalid_argument("Invalid num of arguements");
    }

    SHARED_DATA sharedData;    

    int option = 0;
   
   /*Contains the code for optional arguements for command line
    * p: number of progress marks (either hyphen or #) for displaying 100% progress of a thread execution, default is 50 if not specified.
    * m: place a hash mark “#” in the progress bar every N characters, default is 1
    * v: print number of contained vocab strings to an output file only it is equal to or greater than N, default is 0 if not specified
    */
    while ((option = getopt(argc, argv, "p:m:v:")) != -1) {
        switch (option) {
            
            case 'p':
                //converts to int
                sharedData.numOfProgressMarks = atoi(optarg);
                if (sharedData.numOfProgressMarks < 10){
                    cerr << "Number of progress marks must be a number and at least 10." << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'm':
                sharedData.hashmarkInterval = atoi(optarg);
                if (sharedData.hashmarkInterval <= 0 || sharedData.hashmarkInterval > 10) {
                    cerr << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10." << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'v':
                sharedData.minNumOfVocabStringsContainedForPrinting = atoi(optarg);
                break;
            default:
                cout << "Usage: " << argv[0] << " vocabulary.txt testfile.txt [-p progressMarks] [-m hashmarkInterval] [-v minNumOfVocabStrings]" << endl;
                exit(1);
        }
    }

    //for vocab file
    sharedData.fileName[VOCABFILEINDEX] = argv[optind];

    //for test file
    sharedData.fileName[TESTFILEINDEX] = argv[optind + 1];

    sharedData.initilize();


    // sharedData.fileName[0] = argv[1]; //for vocab file
    // sharedData.fileName[1] = argv[2]; //for test file
    

    pthread_t readvocabThread;
    pthread_t readlinesThread;
    pthread_t countvocabstringsThread;

    
    
    pthread_mutex_init(&sharedData.queue_mutex,NULL);

    //??not sure how to pass the files
    if (pthread_create(&readvocabThread, NULL, &readvocab, (void*)&sharedData)){
        cerr << "Error creating readvocabThread" << endl;
        exit(1);
    }

    if (pthread_create(&readlinesThread, NULL, &readlines, (void*)&sharedData)){
        cerr << "Error creating readlinesThread" << endl;
        exit(1);
    }

    pthread_create(&countvocabstringsThread, NULL, &countvocabstrings, (void*)&sharedData);

    displayVocabProgress(&sharedData);

    displayCountVocabProgress(&sharedData);

    //waits for threads to be done
    pthread_join(readvocabThread, NULL);
    pthread_join(readlinesThread, NULL);
    pthread_join(countvocabstringsThread, NULL);

    

    return 0;

}  

