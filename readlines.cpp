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

    pthread_mutex_lock(&(accessData->queue_mutex));
    while(std::getline(testIn, testLine)){

        std::transform(testLine.begin(), testLine.end(), testLine.begin(), ::tolower);
        accessData->lineQueue.push(testLine);
        accessData->lineCountInFile[TESTFILEINDEX]++;
    }
    pthread_mutex_unlock(&(accessData->queue_mutex));

    //locks access to queue while testfile is still being read
    
    
    accessData->taskCompleted[TESTFILEINDEX] = true;
    
    

   
    pthread_exit(NULL);
}
