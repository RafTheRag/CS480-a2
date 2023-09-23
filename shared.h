#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>
#include <queue>
#include <vector>
#include <string>

#define NUMOFFILES 2
#define VOCABFILEINDEX 0
#define TESTFILEINDEX 1

#define DEFAULT_NUMOF_MARKS 50
#define MIN_NUMOF_MARKS 10
#define DEFAULT_HASHMARKINTERVAL 10
#define DEFAULT_MINNUM_OFVOCABSTRINGS_CONTAINED 0

typedef struct {
    unsigned int numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    unsigned int hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    unsigned int minNumOfVocabStringsContainedForPrinting = DEFAULT_MINNUM_OFVOCABSTRINGS_CONTAINED;
    const char* fileName[NUMOFFILES];
    unsigned long totalNumOfCharsInVocabFile;
    long numOfCharsReadFromVocabFile;
    long lineCountInFile[NUMOFFILES];
    long numOfProcessedLines;
    std::vector<std::string> *vocabVect;
    std::queue<std::string> *lineQueue;
    pthread_mutex_t queue_mutex;
    bool taskCompleted[NUMOFFILES];
} SHARED_DATA;

#endif // SHARED_H
