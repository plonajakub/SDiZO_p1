#ifndef SDIZO_P1_TIMEMEASUREMENT_H
#define SDIZO_P1_TIMEMEASUREMENT_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <random>
#include <exception>
#include <climits>
#include <functional>

#include "../data_structures/Table.h"
#include "../data_structures/DoublyLinkedList.h"
#include "../data_structures/Heap.h"
#include "../data_structures/RedBlackTree.h"

using std::cout;
using std::endl;

class MeasurementPoint {
public:
    // Size of structure
    int size;
    // Time of structure's operation
    long double time;
};

class TimeMeasurement {
public:

    // Constructor
    TimeMeasurement();

    // Start time measurement
    void run();

private:

    // Number of repeated operations of the same type with the same size
    static const int DRAWS_NUMBER = 4;

    // Investigated intervals of data in structures
    static const int INTERVALS_OF_VALUES = 5;

    // Upper limit for data count in structures
    static const int DATA_COUNT = 5000;

    const std::string intervals[INTERVALS_OF_VALUES] = {
            std::string("[0; INT_MAX / 2]"),
            std::string("[INT_MAX / 2; INT_MAX]"),
            std::string("[0; INT_MAX]"),
            std::string("[0; 100]"),
            std::string("[INT_MAX - 100; INT_MAX]")
    };

    // Investigated structures
    Table *table;
    DoublyLinkedList *dll;
    Heap *heap;
    RedBlackTree *rbt;

    MeasurementPoint **createMeasurementPointTable();

    void deleteMeasurementPointTable(MeasurementPoint **mpsTable);

    // Returns random value from [leftLimit, rightLimit] interval
    int getRand(int leftLimit, int rightLimit);

    // Start time stamp (saved in *start)
    void startTimer(LARGE_INTEGER *start);

    // End time stamp (saved in *stop)
    void endTimer(LARGE_INTEGER *stop);

    // Calculate time of an operation (here function) in microseconds
    long double countTime(const std::function<void()> &function);

    // Saves collected data about structure method's time in CSV format
    void saveTimeDataToFile(const std::string &fileName,
                            const std::string (&dataRanges)[INTERVALS_OF_VALUES],
                            MeasurementPoint **measurementPoints);

    void analyzeTableInsertBeg();

    void analyzeTableInsertEnd();

    void analyzeTableInsertRand();

    void analyzeTableRemoveBeg();

    void analyzeTableRemoveEnd();

    void analyzeTableRemoveRand();

    void analyzeTableSearch();
};


#endif //SDIZO_P1_TIMEMEASUREMENT_H
