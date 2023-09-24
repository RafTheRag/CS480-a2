#include "readlines.h" 
#include <fstream>
#include <string>
#include <algorithm>

void* readlines(void* arg){
    
    SHARED_DATA *accessData = (SHARED_DATA*)arg;
    
    const char* testFileName = accessData->fileName[TESTFILEINDEX];
    accessData->lineCountInFile[TESTFILEINDEX] = 0;
    
    //Preperation for reading in test file lines.
    std::ifstream testIn(testFileName);
    std::string testLine;

    //locks access to queue while testfile is still being read
    pthread_mutex_lock(&(accessData->queue_mutex));


    while(std::getline(testIn, testLine)){

        std::transform(testLine.begin(), testLine.end(), testLine.begin(), ::tolower);
        accessData->lineQueue.push(testLine);
        accessData->lineCountInFile[TESTFILEINDEX]++;
    }
    
    //unlocks access to queue after being read
    
    accessData->taskCompleted[TESTFILEINDEX] = true;
    pthread_cond_signal(&accessData->condition);
    
    pthread_mutex_unlock(&(accessData->queue_mutex));
    pthread_exit(NULL);
}
