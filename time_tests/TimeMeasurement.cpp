#include "TimeMeasurement.h"

TimeMeasurement::TimeMeasurement() : table(nullptr), dll(nullptr), heap(nullptr), rbt(nullptr) {
}

void TimeMeasurement::run() {
//    analyzeTableInsertBeg();
//    analyzeTableInsertEnd();
//    analyzeTableInsertRand();
    analyzeTableRemoveBeg();
    analyzeTableRemoveEnd();
    analyzeTableRemoveRand();
    analyzeTableSearch();
}

int TimeMeasurement::getRand(int leftLimit, int rightLimit) {
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::uniform_int_distribution<>(leftLimit, rightLimit)(gen);
}

long double TimeMeasurement::countTime(const std::function<void()> &function) {
    LARGE_INTEGER startingTime, endingTime, elapsedMicroseconds;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    startTimer(&startingTime);
    function();
    endTimer(&endingTime);
    elapsedMicroseconds.QuadPart = endingTime.QuadPart - startingTime.QuadPart;

    elapsedMicroseconds.QuadPart *= 1000000;
    elapsedMicroseconds.QuadPart /= frequency.QuadPart;
    return elapsedMicroseconds.QuadPart;
}

void
TimeMeasurement::saveTimeDataToFile(const std::string &fileName, const std::string (&dataRanges)[INTERVALS_OF_VALUES],
                                    MeasurementPoint **measurementPoints) {
    const char sep = ',';
    std::ofstream file("../time_tests/data/" + fileName, std::ofstream::trunc);
    if (!file.is_open()) {
        throw std::ios_base::failure(fileName + " not opened!");
    }

    cout << "Writing file " + fileName + "...";
    file << "Ilosc elementow w strukturze";
    for (const auto &columnName : dataRanges) {
        file << sep << columnName;
    }
    file << endl;

    for (int i = 0; i < DATA_COUNT; ++i) {
        for (int j = 0; j < INTERVALS_OF_VALUES - 1; ++j) {
            if (measurementPoints[i][j].size != measurementPoints[i][j + 1].size) {
                throw std::exception();
            }
        }
        file << measurementPoints[i][0].size;
        for (int j = 0; j < INTERVALS_OF_VALUES; ++j) {
            file << sep << measurementPoints[i][j].time;
        }
        file << endl;
    }
    cout << "written!" << endl;
    file.close();
}

void TimeMeasurement::startTimer(LARGE_INTEGER *start) {
    DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(start);
    SetThreadAffinityMask(GetCurrentThread(), oldMask);
}

void TimeMeasurement::endTimer(LARGE_INTEGER *stop) {
    DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(stop);
    SetThreadAffinityMask(GetCurrentThread(), oldMask);
}

MeasurementPoint **TimeMeasurement::createMeasurementPointTable() {
    auto **mpsTable = new MeasurementPoint *[DATA_COUNT]();
    for (int i = 0; i < DATA_COUNT; ++i) {
        mpsTable[i] = new MeasurementPoint[INTERVALS_OF_VALUES]();
    }
    return mpsTable;
}

void TimeMeasurement::deleteMeasurementPointTable(MeasurementPoint **mpsTable) {
    for (int i = 0; i < DATA_COUNT; ++i) {
        delete[] mpsTable[i];
    }
    delete[] mpsTable;
}

void TimeMeasurement::analyzeTableInsertBeg() {
    MeasurementPoint **mpsTableInsertBeg = createMeasurementPointTable();
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableInsertBeg[i][intervalIdx].size = table->getSize();
                switch (intervalIdx) {
                    case 0:
                        mpsTableInsertBeg[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(0, INT_MAX / 2)); });
                        break;
                    case 1:
                        mpsTableInsertBeg[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(INT_MAX / 2, INT_MAX)); });
                        break;
                    case 2:
                        mpsTableInsertBeg[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(0, INT_MAX)); });
                        break;
                    case 3:
                        mpsTableInsertBeg[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(0, 100)); });
                        break;
                    case 4:
                        mpsTableInsertBeg[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(INT_MAX - 100, INT_MAX)); });
                        break;
                    default:
                        throw std::exception();
                }
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    for (int i = 0; i < DATA_COUNT; ++i) {
        for (int j = 0; j < INTERVALS_OF_VALUES; ++j) {
            mpsTableInsertBeg[i][j].time /= DRAWS_NUMBER;
        }
    }
    this->saveTimeDataToFile("table/mpsTableInsertBeg.csv", intervals, mpsTableInsertBeg);
    deleteMeasurementPointTable(mpsTableInsertBeg);
}

void TimeMeasurement::analyzeTableInsertEnd() {
    MeasurementPoint **mpsTableInsertEnd = createMeasurementPointTable();
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertEnd: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableInsertEnd[i][intervalIdx].size = table->getSize();
                switch (intervalIdx) {
                    case 0:
                        mpsTableInsertEnd[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtEnd(this->getRand(0, INT_MAX / 2)); });
                        break;
                    case 1:
                        mpsTableInsertEnd[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtEnd(this->getRand(INT_MAX / 2, INT_MAX)); });
                        break;
                    case 2:
                        mpsTableInsertEnd[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtEnd(this->getRand(0, INT_MAX)); });
                        break;
                    case 3:
                        mpsTableInsertEnd[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtEnd(this->getRand(0, 100)); });
                        break;
                    case 4:
                        mpsTableInsertEnd[i][intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtEnd(this->getRand(INT_MAX - 100, INT_MAX)); });
                        break;
                    default:
                        throw std::exception();
                }
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    for (int i = 0; i < DATA_COUNT; ++i) {
        for (int j = 0; j < INTERVALS_OF_VALUES; ++j) {
            mpsTableInsertEnd[i][j].time /= DRAWS_NUMBER;
        }
    }
    this->saveTimeDataToFile("table/mpsTableInsertEnd.csv", intervals, mpsTableInsertEnd);
    deleteMeasurementPointTable(mpsTableInsertEnd);
}

void TimeMeasurement::analyzeTableInsertRand() {
    MeasurementPoint **mpsTableInsertRand = createMeasurementPointTable();
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertRand: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableInsertRand[i][intervalIdx].size = table->getSize();
                switch (intervalIdx) {
                    case 0:
                        mpsTableInsertRand[i][intervalIdx].time += this->countTime(
                                [&]() -> void {
                                    table->insert(this->getRand(0, table->getSize()),
                                                  this->getRand(0, INT_MAX / 2));
                                });
                        break;
                    case 1:
                        mpsTableInsertRand[i][intervalIdx].time += this->countTime(
                                [&]() -> void {
                                    table->insert(this->getRand(0, table->getSize()),
                                                  this->getRand(INT_MAX / 2, INT_MAX));
                                });
                        break;
                    case 2:
                        mpsTableInsertRand[i][intervalIdx].time += this->countTime(
                                [&]() -> void {
                                    table->insert(this->getRand(0, table->getSize()),
                                                  this->getRand(0, INT_MAX));
                                });
                        break;
                    case 3:
                        mpsTableInsertRand[i][intervalIdx].time += this->countTime(
                                [&]() -> void {
                                    table->insert(this->getRand(0, table->getSize()),
                                                  this->getRand(0, 100));
                                });
                        break;
                    case 4:
                        mpsTableInsertRand[i][intervalIdx].time += this->countTime(
                                [&]() -> void {
                                    table->insert(this->getRand(0, table->getSize()),
                                                  this->getRand(INT_MAX - 100, INT_MAX));
                                });
                        break;
                    default:
                        throw std::exception();
                }
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    for (int i = 0; i < DATA_COUNT; ++i) {
        for (int j = 0; j < INTERVALS_OF_VALUES; ++j) {
            mpsTableInsertRand[i][j].time /= DRAWS_NUMBER;
        }
    }
    this->saveTimeDataToFile("table/mpsTableInsertRand.csv", intervals, mpsTableInsertRand);
    deleteMeasurementPointTable(mpsTableInsertRand);
}

void TimeMeasurement::analyzeTableRemoveBeg() {
    MeasurementPoint **mpsTableRemoveBeg = createMeasurementPointTable();
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableRemoveBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                switch (intervalIdx) {
                    case 0:
                        table->insertAtEnd(this->getRand(0, INT_MAX / 2));
                        break;
                    case 1:
                        table->insertAtEnd(this->getRand(INT_MAX / 2, INT_MAX));
                        break;
                    case 2:
                        table->insertAtEnd(this->getRand(0, INT_MAX));
                        break;
                    case 3:
                        table->insertAtEnd(this->getRand(0, 100));
                        break;
                    case 4:
                        table->insertAtEnd(this->getRand(INT_MAX - 100, INT_MAX));
                        break;
                    default:
                        throw std::exception();
                }
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableRemoveBeg[i][intervalIdx].size = table->getSize();
                mpsTableRemoveBeg[i][intervalIdx].time += this->countTime([&]() -> void {
                    table->removeFromStart();
                });
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    for (int i = 0; i < DATA_COUNT; ++i) {
        for (int j = 0; j < INTERVALS_OF_VALUES; ++j) {
            mpsTableRemoveBeg[i][j].time /= DRAWS_NUMBER;
        }
    }
    auto **mpsTableRemoveBegReversed = new MeasurementPoint *[DATA_COUNT]();
    for (int i = 0, j = DATA_COUNT - 1; i < DATA_COUNT; ++i, --j) {
        mpsTableRemoveBegReversed[i] = mpsTableRemoveBeg[j];
    }
    this->saveTimeDataToFile("table/mpsTableRemoveBeg.csv", intervals, mpsTableRemoveBegReversed);
    deleteMeasurementPointTable(mpsTableRemoveBeg);
    delete[] mpsTableRemoveBegReversed;
}

void TimeMeasurement::analyzeTableRemoveEnd() {

}

void TimeMeasurement::analyzeTableRemoveRand() {

}

void TimeMeasurement::analyzeTableSearch() {

}
