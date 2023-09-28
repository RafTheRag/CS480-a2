/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
#include "countvocabstrings.h" 
#include "tree.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

void* countvocabstrings(void* arg){
    //create pointer to Shared_Data structure
    SHARED_DATA *accessData = (SHARED_DATA*)arg;


    //busy wait that checks if the readVocab Thread is done or that the queue is not empty
    while(!accessData->taskCompleted[VOCABFILEINDEX] || accessData->lineQueue.empty()){
        continue;
    }

    int vocabCount;
    
    //used to write number of found substrings to this file
    std::ofstream vocabCountOut("countNumOfContainedVocab.txt");
    
    //loop while 
    while(!accessData->lineQueue.empty()){
        
        vocabCount = 0;
        CharTrie charTrie;
        const char* frontOfQueue = accessData->lineQueue.front().c_str();
        //calls insert method that inserts all possible substrings into the trie
        charTrie.insert(frontOfQueue);

        //Creates mutex lock and unlock to not allow access to readlines while countvocabstrings is still accessing queue
        pthread_mutex_lock(&(accessData->queue_mutex));
        for(auto &vocab: accessData->vocabVect){
            if(charTrie.search(vocab.c_str())){  //calls search method and returns true every time a valid substring is called
                vocabCount++;
            }
        }
        
        accessData->lineQueue.pop();
        pthread_mutex_unlock(&(accessData->queue_mutex));

        //compares vocab count to the minimum number that should be printed out, given by the v optional arguement/default
        if(vocabCount >= accessData->minNumOfVocabStringsContainedForPrinting){
            vocabCountOut << vocabCount << std::endl;
        }

        //itterates every time a line is processed
        accessData->numOfProcessedLines++;
        
    }

    vocabCountOut.close();
    
    
    pthread_exit(NULL);



}