#include "TimeMeasurement.h"

TimeMeasurement::TimeMeasurement() : table(nullptr), dll(nullptr), heap(nullptr), rbt(nullptr) {
}

void TimeMeasurement::run() {
    analyzeTableInsertBeg();
    analyzeTableInsertEnd();
    analyzeTableInsertRand();
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

int TimeMeasurement::getIntervalValue(int intervalIndex) {
    switch (intervalIndex) {
        case 0:
            return this->getRand(0, INT_MAX / 2);
        case 1:
            return this->getRand(INT_MAX / 2, INT_MAX);
        case 2:
            return this->getRand(0, INT_MAX);
        case 3:
            return this->getRand(0, 100);
        case 4:
            return this->getRand(INT_MAX - 100, INT_MAX);
        default:
            throw std::exception();
    }
}

double TimeMeasurement::countTime(const std::function<void()> &function) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double nanoseconds_per_count = 1.0e9 / static_cast<double>(freq.QuadPart);

    LARGE_INTEGER time1, time2;
    this->startTimer(&time1);
    function();
    this->endTimer(&time2);

    return (time2.QuadPart - time1.QuadPart) * nanoseconds_per_count;
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

void TimeMeasurement::divideEachTimeByDrawsNumber(MeasurementPoint **mps) {
    for (int i = 0; i < DATA_COUNT; ++i) {
        for (int j = 0; j < INTERVALS_OF_VALUES; ++j) {
            mps[i][j].time /= DRAWS_NUMBER;
        }
    }
}

void TimeMeasurement::reverseMPS(MeasurementPoint **mps) {
    MeasurementPoint *temp;
    for (int i = 0, j = DATA_COUNT - 1; i < j; ++i, --j) {
        temp = mps[i];
        mps[i] = mps[j];
        mps[j] = temp;
    }
}

void TimeMeasurement::analyzeTableInsertBeg() {
    MeasurementPoint **mpsTableInsertBeg = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableInsertBeg[i][intervalIdx].size = table->getSize();
                value = this->getIntervalValue(intervalIdx);
                mpsTableInsertBeg[i][intervalIdx].time += this->countTime(
                        [&]() -> void { table->insertAtStart(value); });
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsTableInsertBeg);
    this->saveTimeDataToFile("table/mpsTableInsertBeg.csv", intervals, mpsTableInsertBeg);
    this->deleteMeasurementPointTable(mpsTableInsertBeg);
}

void TimeMeasurement::analyzeTableInsertEnd() {
    MeasurementPoint **mpsTableInsertEnd = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertEnd: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableInsertEnd[i][intervalIdx].size = table->getSize();
                value = this->getIntervalValue(intervalIdx);
                mpsTableInsertEnd[i][intervalIdx].time += this->countTime(
                        [&]() -> void { table->insertAtEnd(value); });
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsTableInsertEnd);
    this->saveTimeDataToFile("table/mpsTableInsertEnd.csv", intervals, mpsTableInsertEnd);
    this->deleteMeasurementPointTable(mpsTableInsertEnd);
}

void TimeMeasurement::analyzeTableInsertRand() {
    MeasurementPoint **mpsTableInsertRand = createMeasurementPointTable();
    int tabIndex, value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertRand: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableInsertRand[i][intervalIdx].size = table->getSize();
                tabIndex = this->getRand(0, table->getSize());
                value = this->getIntervalValue(intervalIdx);
                mpsTableInsertRand[i][intervalIdx].time += this->countTime(
                        [&]() -> void {
                            table->insert(tabIndex, value);
                        });
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsTableInsertRand);
    this->saveTimeDataToFile("table/mpsTableInsertRand.csv", intervals, mpsTableInsertRand);
    this->deleteMeasurementPointTable(mpsTableInsertRand);
}

void TimeMeasurement::analyzeTableRemoveBeg() {
    MeasurementPoint **mpsTableRemoveBeg = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableRemoveBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                value = this->getIntervalValue(intervalIdx);
                table->insertAtEnd(value);
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
    this->divideEachTimeByDrawsNumber(mpsTableRemoveBeg);
    this->reverseMPS(mpsTableRemoveBeg);
    this->saveTimeDataToFile("table/mpsTableRemoveBeg.csv", intervals, mpsTableRemoveBeg);
    this->deleteMeasurementPointTable(mpsTableRemoveBeg);
}

void TimeMeasurement::analyzeTableRemoveEnd() {
    MeasurementPoint **mpsTableRemoveEnd = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableRemoveEnd: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                value = this->getIntervalValue(intervalIdx);
                table->insertAtEnd(value);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableRemoveEnd[i][intervalIdx].size = table->getSize();
                mpsTableRemoveEnd[i][intervalIdx].time += this->countTime([&]() -> void {
                    table->removeFromEnd();
                });
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsTableRemoveEnd);
    this->reverseMPS(mpsTableRemoveEnd);
    this->saveTimeDataToFile("table/mpsTableRemoveEnd.csv", intervals, mpsTableRemoveEnd);
    this->deleteMeasurementPointTable(mpsTableRemoveEnd);
}

void TimeMeasurement::analyzeTableRemoveRand() {
    MeasurementPoint **mpsTableRemoveRand = createMeasurementPointTable();
    int tabIndex, value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableRemoveRand: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                value = this->getIntervalValue(intervalIdx);
                table->insertAtEnd(value);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsTableRemoveRand[i][intervalIdx].size = table->getSize();
                tabIndex = this->getRand(0, table->getSize() - 1);
                mpsTableRemoveRand[i][intervalIdx].time += this->countTime([&]() -> void {
                    table->remove(tabIndex);
                });
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsTableRemoveRand);
    this->reverseMPS(mpsTableRemoveRand);
    this->saveTimeDataToFile("table/mpsTableRemoveRand.csv", intervals, mpsTableRemoveRand);
    this->deleteMeasurementPointTable(mpsTableRemoveRand);
}

void TimeMeasurement::analyzeTableSearch() {
    MeasurementPoint **mpsTableSearch = createMeasurementPointTable();
    int insertValue, searchValue;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableSearch: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            table = new Table;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                mpsTableSearch[elIdx][intervalIdx].size = table->getSize();
                insertValue = this->getIntervalValue(intervalIdx);
                searchValue = this->getIntervalValue(intervalIdx);
                mpsTableSearch[elIdx][intervalIdx].time += this->countTime([&]() -> void {
                    table->search(searchValue);
                });
                table->insertAtEnd(insertValue);
            }
            delete table;
            table = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsTableSearch);
    this->saveTimeDataToFile("table/mpsTableSearch.csv", intervals, mpsTableSearch);
    this->deleteMeasurementPointTable(mpsTableSearch);
}

void TimeMeasurement::analyzeListInsertBeg() {

}

void TimeMeasurement::analyzeListInsertEnd() {

}

void TimeMeasurement::analyzeListInsertRand() {

}

void TimeMeasurement::analyzeListRemoveBeg() {

}

void TimeMeasurement::analyzeListRemoveEnd() {

}

void TimeMeasurement::analyzeListRemoveRand() {

}

void TimeMeasurement::analyzeListSearch() {

}




