#include "readvocab.h" 
#include "tree.h"

void* readvocab(void* arg){
    //access shared data structure inside thread
    SHARED_DATA *accessData = (SHARED_DATA*)arg;
    
    struct stat fileStat;
    const char* filePath = accessData->fileName[0];
    stat(filePath, &fileStat);
    accessData->totalNumOfCharsInVocabFile = fileStat.st_size;
    

    
    pthread_exit(NULL);
}