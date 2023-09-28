#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <iostream>
#include "shared.h"


void displayVocabProgress(SHARED_DATA *data){
    double tickPercentage = 100.0 / data->numOfProgressMarks;
    int countOfCurrentMarks = 0;

    while(!data->taskCompleted[VOCABFILEINDEX]){
        double progress = (double)(data->numOfCharsReadFromVocabFile) / (double)(data->totalNumOfCharsInVocabFile);

        //std::cout << sharedData->numOfCharsReadFromVocabFile << std::endl;

        if((countOfCurrentMarks + 1) % data->hashmarkInterval == 0){
            std::cout << '#' << std::flush;
            countOfCurrentMarks++;
            continue;
        }
        if((progress * 100) / tickPercentage >= countOfCurrentMarks + 1){
            std::cout << '-' << std::flush;
            countOfCurrentMarks++;
        }

        //std::cout << progress << std::endl;
    }
    std::cout << std::endl << "There are " << data->lineCountInFile[VOCABFILEINDEX] << " lines in " << data->fileName[VOCABFILEINDEX] << std::endl;

}

void displayCountVocabProgress(SHARED_DATA *data){
    double tickPercentage = 100.0 / data->numOfProgressMarks;
    int countOfCurrentMarks = 0;

    while(!data->lineQueue.empty()){
        double progress = (double)(data->numOfProcessedLines) / (double)(data->lineCountInFile[TESTFILEINDEX]);

        //std::cout << sharedData->numOfCharsReadFromVocabFile << std::endl;

        if((countOfCurrentMarks + 1) % data->hashmarkInterval == 0){
            std::cout << '#' << std::flush;
            countOfCurrentMarks++;
            continue;
        }
        if((progress * 100) / tickPercentage >= countOfCurrentMarks + 1){
            std::cout << '-' << std::flush;
            countOfCurrentMarks++;
        }

        //std::cout << progress << std::endl;
    }
    std::cout << std::endl << "There are " << data->lineCountInFile[TESTFILEINDEX] << " lines in " << data->fileName[TESTFILEINDEX] << std::endl;
}