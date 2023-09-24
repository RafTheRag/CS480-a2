#ifndef SHARED_H
#define SHARED_H

#include <sys/stat.h>
#include <pthread.h>
#include <queue>
#include <vector>
#include <string>
#include <iostream>

#define NUMOFFILES 2
#define VOCABFILEINDEX 0
#define TESTFILEINDEX 1

#define DEFAULT_NUMOF_MARKS 50
#define constant MIN_NUMOF_MARKS 10
#define DEFAULT_HASHMARKINTERVAL 10
#define DEFAULT_MINNUM_OFVOCABSTRINGS_CONTAINED 0

typedef struct {
    /**
    * parameters for printing progress bar
    */
    unsigned int numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    unsigned int hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    unsigned int minNumOfVocabStringsContainedForPrinting = DEFAULT_MINNUM_OFVOCABSTRINGS_CONTAINED;
    
    /**
    * fileName[0] - file path for the vocabulary file
    * fileName[1] - file path for the test file providing lines for testing
    */
    const char* fileName[NUMOFFILES];
    
    /** store total number of characters in files
    * totalNumOfCharsInVocabFile
    * - number of total chars in the dictionary vocabulary file.
    * use stat, lstat, or fstat system call
    */
    unsigned long totalNumOfCharsInVocabFile;
    
    /**
    * Use numOfCharsReadFromVocabFile to track ongoing progress of
    * number of characters read in from vocab file.
    *
    * This progress indicator is updated by readvocab worker thread, and used by the main
    * thread to display the progress for tracking the execution of the readvocab thread
    */
    long numOfCharsReadFromVocabFile;
    
    /**
    * lineCountInFile[VOCABFILEINDEX]
    * - number of total lines (or words) in the vocabulary file.
    * lineCountInFile[TESTFILEINDEX]
    * - number of total lines in the test file
    */
    long lineCountInFile[NUMOFFILES];
    
    /**
    * number of lines that have been removed and processed from
    * the line queue,
    * this is used for tracking the progress of the countvocabstrings thread
    */
    long numOfProcessedLines;
    
    /**
    * store strings read from vocabulary file
    */
    std::vector<std::string> vocabVect;
    
    /**
    * buffer lines read from test file
    */
    std::queue<std::string> lineQueue;
    
    /**
    * pthread mutex for accessing the line Queue
    */
    pthread_mutex_t queue_mutex;
    
    /**
    * completed flags indicate the completion of the thread logic, one
    * for the readvocab thread, one for readlines thread
    */
    bool taskCompleted[NUMOFFILES];
} SHARED_DATA;

#endif // SHARED_H
