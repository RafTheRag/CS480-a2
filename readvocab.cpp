#include "readvocab.h" 
#include "tree.h"

void* readvocab(void* arg){
    //access shared data structure inside thread
    SHARED_DATA *accessData = (SHARED_DATA*)arg;
    
    struct stat fileStat;
    const char* filePath = accessData->fileName[0];
    if (stat(filePath, &fileStat) == -1) {
        std::cerr << "Unable to stat file: " << filePath << std::endl;
    }
    accessData->totalNumOfCharsInVocabFile = fileStat.st_size;

    
    
    pthread_exit(NULL);
}