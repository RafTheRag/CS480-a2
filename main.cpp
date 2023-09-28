/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
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

int main(int argc, char** argv) {
    //checks if there is valid amount of mandatory arguements in the command line
    if (argc < 3) {
        throw invalid_argument("Invalid num of arguements");
    }

    // shared data to be used for communication between threads
    // main thread, readvocab, readlines, countvocabstrings
    SHARED_DATA sharedData;    

    int option = 0;
   
   /*Contains the code for optional arguements for command line
    * p: number of progress marks (either hyphen or #) for displaying 100% progress of a thread execution, default is 50 if not specified.
    * m: place a hash mark “#” in the progress bar every N characters, default is 1
    * v: print number of contained vocab strings to an output file only it is equal to or greater than N, default is 0 if not specified
    * else will send a error if usage was not correct
    */
    while ((option = getopt(argc, argv, "p:m:v:")) != -1) {
        switch (option) {
            
            case 'p':
                sharedData.numOfProgressMarks = atoi(optarg);
                //checks if numOfProgressMarks is greater than 10 to run
                if (sharedData.numOfProgressMarks < 10){
                    cerr << "Number of progress marks must be a number and at least 10." << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'm':
                sharedData.hashmarkInterval = atoi(optarg);
                //checks if hashmarkInterval is greater than 0 and less than or equal to 10 to run
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

    //for vocab file if we are given an invalid vocabFile we diplay an error and exit.
    ifstream vocabFile;
    vocabFile.open(argv[optind]);
    if (!vocabFile){
        cerr << "Display Unable to open <<" << argv[optind] << ">>" << endl;
        exit(1);
    }
    vocabFile.close();
    sharedData.fileName[VOCABFILEINDEX] = argv[optind];


    //for test file if we are given an invalid testFile we diplay an error and exit.
    ifstream testFile;
    testFile.open(argv[optind + 1]);
    if (!testFile){
        cerr << "Display Unable to open <<" << argv[optind + 1] << ">>" << endl;
        exit(1);
    } 
    testFile.close();
    sharedData.fileName[TESTFILEINDEX] = argv[optind + 1];

    //initializes the rest of the variable in the shared data sturcture
    sharedData.initilize();


    
    /* readvocab thread reads in the lines from from vocabualary.txt and inserts them into a shared vector, while also calculating the total
    *  amount of characters and the total number of lines
    */
    pthread_t readvocabThread;

    //readlinesThread thread reads in the lines from from testfile.txt and inserts them into a shared queue, while also calculating the total number of lines
    pthread_t readlinesThread;


    /*countvocabstringsThread must wait for readVocab to be done, when ready uses the shared queue to insert all possible substrings into a Trie.
     * Then uses the shared vector to serch for all valid substrings, and iterates count if true. Finally, prints all number of found substrings for 
     * each line into a text file
    */
    pthread_t countvocabstringsThread;

    
    //initializes queue mutex
    pthread_mutex_init(&sharedData.queue_mutex,NULL);

    // creates and starts readvocabThread 
    // readvocab is the thread function executed by the readvocabThread
    // checks if the thread was successgully created and ran
    if (pthread_create(&readvocabThread, NULL, &readvocab, (void*)&sharedData)){
        cerr << "Error creating readvocabThread" << endl;
        exit(1);
    }

    // creates and starts readlinesThread 
    // readlines is the thread function executed by the readlinesThread
    // checks if the thread was created and ran
    if (pthread_create(&readlinesThread, NULL, &readlines, (void*)&sharedData)){
        cerr << "Error creating readlinesThread" << endl;
        exit(1);
    }

    // creates and starts countvocabstringsThread
    // countvocabstrings is the thread function executed by the countvocabstringsThread
    // checks if the thread was created and ran
    if (pthread_create(&countvocabstringsThread, NULL, &countvocabstrings, (void*)&sharedData)){
        cerr << "Error creating countvocabstringsThread" << endl;
        exit(1);
    }    


    //calls display method for readVocab's progress bar
    displayVocabProgress(&sharedData);

    //calls display method for countvocabstrings's progress bar
    displayCountVocabProgress(&sharedData);

    //waits for threads to be done
    pthread_join(readvocabThread, NULL);
    pthread_join(readlinesThread, NULL);
    pthread_join(countvocabstringsThread, NULL);

    

    exit(0);

}  

