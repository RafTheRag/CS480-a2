/*
*Author Rafael Ramirez & Matt D. Jaranilla
*REDID: 825477088 & 825452453
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <iostream>
#include "display.h"

//Takes in a SHARED_DATA pointer as an argument to cout the progress bar for the readvocab thread.
void displayVocabProgress(SHARED_DATA *data){

    double tickPercentage = MAXPERCENTAGE / data->numOfProgressMarks; //Find the percentage value of individual ticks given the number of progress marks set to print.
    int countOfCurrentMarks = 0;

    while(!data->taskCompleted[VOCABFILEINDEX]){ //Run while readvocab thread is running
        double progress = (double)(data->numOfCharsReadFromVocabFile) / (double)(data->totalNumOfCharsInVocabFile);

        if((progress * 100) / tickPercentage >= countOfCurrentMarks + 1){ //Checks to see if we should print a mark given that our progresspercentage / tickPercentage is within the threshold for the next mark

            if((countOfCurrentMarks + 1) % data->hashmarkInterval == 0){ //If our next mark is a multiple of our hashmark interval we make the next mark a hashtag. else print a -.
            std::cout << '#' << std::flush;
            countOfCurrentMarks++;

            }else{
            std::cout << '-' << std::flush;
            countOfCurrentMarks++;
            }
        }
    }

    //We check one more time what symbol we should have signialing our 100% mark.
    if(countOfCurrentMarks < data->numOfProgressMarks){

        if((countOfCurrentMarks + 1) % data->hashmarkInterval == 0){ 

            std::cout << '#' << std::flush;

        }else{

            std::cout << '-' << std::flush;
        }
    }
    
    //Once our readvocab task is complete we cout the total number of lines in the vocab file.
    std::cout << std::endl << "There are " << data->lineCountInFile[VOCABFILEINDEX] << " lines in " << data->fileName[VOCABFILEINDEX] << std::endl;

}

//Takes in a SHARED_DATA pointer as an argument to cout the progress bar for the countvocabstrings thread.
void displayCountVocabProgress(SHARED_DATA *data){
    double tickPercentage = MAXPERCENTAGE / data->numOfProgressMarks; //Find the percentage value of individual ticks given the number of progress marks set to print.
    int countOfCurrentMarks = 0;

    while(!data->lineQueue.empty()){
        double progress = (double)(data->numOfProcessedLines) / (double)(data->lineCountInFile[TESTFILEINDEX]);

        if((progress * 100) / tickPercentage >= countOfCurrentMarks + 1){ //Checks to see if we should print a mark given that our progresspercentage / tickPercentage is within the threshold for the next mark
            if((countOfCurrentMarks + 1) % data->hashmarkInterval == 0){ //If our next mark is a multiple of our hashmark interval we make the next mark a hashtag. else print a -.
            std::cout << '#' << std::flush;
            countOfCurrentMarks++;
            }else{
            std::cout << '-' << std::flush;
            countOfCurrentMarks++;
            }
        }
    }

    //We check one more time what symbol we should have signialing our 100% mark
    if(countOfCurrentMarks < data->numOfProgressMarks){

        if((countOfCurrentMarks + 1) % data->hashmarkInterval == 0){ //We check one more time what symbol we should have signialing our 100% mark

            std::cout << '#' << std::flush;

        }else{

            std::cout << '-' << std::flush;
        }
    }

    //Once our readvocab task is complete we cout the total number of lines in the test file.
    std::cout << std::endl << "There are " << data->lineCountInFile[TESTFILEINDEX] << " lines in " << data->fileName[TESTFILEINDEX] << std::endl;
}