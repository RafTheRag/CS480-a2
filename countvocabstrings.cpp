
#include "countvocabstrings.h" 
#include "tree.h"
#include "shared.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

void* countvocabstrings(void* arg){
    SHARED_DATA *accessData = (SHARED_DATA*)arg;


    
    while(!accessData->taskCompleted[VOCABFILEINDEX] || accessData->lineQueue.empty()){
        continue;
    }

    int vocabCount;

    std::ofstream vocabCountOut("countNumOfContainedVocab.txt");
    
    while(!accessData->lineQueue.empty()){
        
        vocabCount = 0;
        CharTrie charTrie;
        const char* frontOfQueue = accessData->lineQueue.front().c_str();
        
        charTrie.insert(frontOfQueue);

        pthread_mutex_lock(&(accessData->queue_mutex));
        for(auto &vocab: accessData->vocabVect){
            if(charTrie.search(vocab.c_str())){
                vocabCount++;
            }
        }

        accessData->lineQueue.pop();
        pthread_mutex_unlock(&(accessData->queue_mutex));


        if(vocabCount >= accessData->minNumOfVocabStringsContainedForPrinting){
            vocabCountOut << vocabCount << std::endl;
        }

        accessData->numOfProcessedLines++;
        
    }

    vocabCountOut.close();
    
    
    pthread_exit(NULL);



}