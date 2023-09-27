#include "countvocabstrings.h" 
#include "tree.h"
#include "shared.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

void* countvocabstrings(void* arg){
    SHARED_DATA *accessData = (SHARED_DATA*)arg;


    
    while(!accessData->taskCompleted[VOCABFILEINDEX] || accessData->lineQueue.empty()){
        continue;
    }

    int vocabCount;
    
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



        //charTrie.~CharTrie();
        if(vocabCount >= accessData->minNumOfVocabStringsContainedForPrinting){
        std::cout << vocabCount << std::endl;
        }
        
    }
    
    
    pthread_exit(NULL);



}