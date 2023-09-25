#include "countvocabstrings.h" 
#include "tree.h"
#include "shared.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

void* countvocabstrings(void* arg){
    SHARED_DATA *accessData = (SHARED_DATA*)arg;
    std::queue<std::string> lineQueue = accessData->lineQueue;

    //busy wait method for mutex going to keep locking and unlocking until bool signal
    while (true) {
        pthread_mutex_lock(&(accessData->queue_mutex));
        if (accessData->taskCompleted[TESTFILEINDEX] == true) {
            pthread_mutex_unlock(&(accessData->queue_mutex));
            break;
        }
        pthread_mutex_unlock(&(accessData->queue_mutex));
    }

    
    // while(!accessData->taskCompleted[VOCABFILEINDEX] || lineQueue.empty()){
    //     sleep(0);
    // }

    while(!lineQueue.empty()){
        
        int vocabCount = 0;
        CharTrie charTrie;
        const char* frontOfQueue = lineQueue.front().c_str();
        charTrie.insert(frontOfQueue);

        for(auto &vocab: accessData->vocabVect){
            if(charTrie.search(vocab.c_str())){
                vocabCount++;
            }
            
        }

        //charTrie.~CharTrie(); Deallocated Trie with deconstructer
        if(vocabCount >= accessData->minNumOfVocabStringsContainedForPrinting){
            std::cout << vocabCount << std::endl;
        }

    }




}