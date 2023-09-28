/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
#include "readlines.h" 
#include <fstream>
#include <string>
#include <algorithm>

void* readlines(void* arg){

    //create pointer to Shared_Data structure
    SHARED_DATA *accessData = (SHARED_DATA*)arg;

    const char* testFileName = accessData->fileName[TESTFILEINDEX];
    
    //Preperation for reading in test file lines.
    std::ifstream testIn(testFileName);
    std::string testLine;

    //Creates mutex lock and unlock to not allow access to countvocabstrings while readlines is still accessing queue
    pthread_mutex_lock(&(accessData->queue_mutex));
    
    // while reads line into shared queue and counts the total number of lines in testfile.txt
    while(std::getline(testIn, testLine)){

        std::transform(testLine.begin(), testLine.end(), testLine.begin(), ::tolower);
        accessData->lineQueue.push(testLine);
        accessData->lineCountInFile[TESTFILEINDEX]++;
    }
    pthread_mutex_unlock(&(accessData->queue_mutex));
    
    //set true to allow to indicate the thread is done
    accessData->taskCompleted[TESTFILEINDEX] = true;
    pthread_exit(NULL);
}
