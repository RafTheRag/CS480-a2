#include "readvocab.h" 
#include "shared.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/stat.h>

void* readvocab(void* arg){
    //Access shared data structure inside thread.
    SHARED_DATA* accessData = (SHARED_DATA*)arg;
    const char* vocabFileName = accessData->fileName[VOCABFILEINDEX];

    //Preperation for reading in vocab file lines.
    std::ifstream vocabIn(vocabFileName);
    std::string vocabLine;

    //Used stat to obtain the number of lines in vocab file .
    struct stat fileStat;
    const char* filePath = vocabFileName;
    stat(filePath, &fileStat);
    accessData->totalNumOfCharsInVocabFile = fileStat.st_size;
    

    //Read in all the lines from vocab file, turn them to lowercase letters, and push to shared vocab vector while increasing the shared count fo the number of total lines processed vector.
    while(std::getline(vocabIn, vocabLine)){

        std::transform(vocabLine.begin(), vocabLine.end(), vocabLine.begin(), ::tolower);
        accessData->vocabVect.push_back(vocabLine);
        accessData->numOfCharsReadFromVocabFile += vocabLine.length() + 1;
    }

    
    //Change shared taskCompleted at index of vocab file to true to indicated completion of readvocab thread.
    accessData->taskCompleted[VOCABFILEINDEX] = true;
    
    //End thread.
    pthread_exit(NULL);
}