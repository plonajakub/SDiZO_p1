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
    analyzeListInsertBeg();
    analyzeListInsertEnd();
    analyzeListInsertRand();
    analyzeListRemoveBeg();
    analyzeListRemoveEnd();
    analyzeListRemoveRand();
    analyzeListSearch();
    analyzeHeapInsert();
    analyzeHeapRemove();
    analyzeHeapSearch();
    analyzeRBTInsert();
    analyzeRBTRemove();
    analyzeRBTSearch();
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
    MeasurementPoint **mpsListInsertBeg = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListInsertBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsListInsertBeg[i][intervalIdx].size = dll->getSize();
                value = this->getIntervalValue(intervalIdx);
                mpsListInsertBeg[i][intervalIdx].time += this->countTime(
                        [&]() -> void { dll->insertAtStart(value); });
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListInsertBeg);
    this->saveTimeDataToFile("list/mpsListInsertBeg.csv", intervals, mpsListInsertBeg);
    this->deleteMeasurementPointTable(mpsListInsertBeg);
}

void TimeMeasurement::analyzeListInsertEnd() {
    MeasurementPoint **mpsListInsertEnd = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListInsertEnd: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsListInsertEnd[i][intervalIdx].size = dll->getSize();
                value = this->getIntervalValue(intervalIdx);
                mpsListInsertEnd[i][intervalIdx].time += this->countTime(
                        [&]() -> void { dll->insertAtEnd(value); });
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListInsertEnd);
    this->saveTimeDataToFile("list/mpsListInsertEnd.csv", intervals, mpsListInsertEnd);
    this->deleteMeasurementPointTable(mpsListInsertEnd);
}

void TimeMeasurement::analyzeListInsertRand() {
    MeasurementPoint **mpsListInsertRand = createMeasurementPointTable();
    int listIndex, value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListInsertRand: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsListInsertRand[i][intervalIdx].size = dll->getSize();
                listIndex = this->getRand(0, dll->getSize());
                value = this->getIntervalValue(intervalIdx);
                mpsListInsertRand[i][intervalIdx].time += this->countTime(
                        [&]() -> void {
                            dll->insert(listIndex, value);
                        });
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListInsertRand);
    this->saveTimeDataToFile("list/mpsListInsertRand.csv", intervals, mpsListInsertRand);
    this->deleteMeasurementPointTable(mpsListInsertRand);
}

void TimeMeasurement::analyzeListRemoveBeg() {
    MeasurementPoint **mpsListRemoveBeg = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListRemoveBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                value = this->getIntervalValue(intervalIdx);
                dll->insertAtEnd(value);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsListRemoveBeg[i][intervalIdx].size = dll->getSize();
                mpsListRemoveBeg[i][intervalIdx].time += this->countTime([&]() -> void {
                    dll->removeFromStart();
                });
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListRemoveBeg);
    this->reverseMPS(mpsListRemoveBeg);
    this->saveTimeDataToFile("list/mpsListRemoveBeg.csv", intervals, mpsListRemoveBeg);
    this->deleteMeasurementPointTable(mpsListRemoveBeg);
}

void TimeMeasurement::analyzeListRemoveEnd() {
    MeasurementPoint **mpsListRemoveEnd = createMeasurementPointTable();
    int value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListRemoveEnd: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                value = this->getIntervalValue(intervalIdx);
                dll->insertAtEnd(value);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsListRemoveEnd[i][intervalIdx].size = dll->getSize();
                mpsListRemoveEnd[i][intervalIdx].time += this->countTime([&]() -> void {
                    dll->removeFromEnd();
                });
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListRemoveEnd);
    this->reverseMPS(mpsListRemoveEnd);
    this->saveTimeDataToFile("list/mpsListRemoveEnd.csv", intervals, mpsListRemoveEnd);
    this->deleteMeasurementPointTable(mpsListRemoveEnd);
}

void TimeMeasurement::analyzeListRemoveRand() {
    MeasurementPoint **mpsListRemoveRand = createMeasurementPointTable();
    int listIndex, value;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListRemoveRand: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                value = this->getIntervalValue(intervalIdx);
                dll->insertAtEnd(value);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsListRemoveRand[i][intervalIdx].size = dll->getSize();
                listIndex = this->getRand(0, dll->getSize() - 1);
                mpsListRemoveRand[i][intervalIdx].time += this->countTime([&]() -> void {
                    dll->remove(listIndex);
                });
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListRemoveRand);
    this->reverseMPS(mpsListRemoveRand);
    this->saveTimeDataToFile("list/mpsListRemoveRand.csv", intervals, mpsListRemoveRand);
    this->deleteMeasurementPointTable(mpsListRemoveRand);
}

void TimeMeasurement::analyzeListSearch() {
    MeasurementPoint **mpsListSearch = createMeasurementPointTable();
    int insertValue, searchValue;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsListSearch: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            dll = new DoublyLinkedList;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                mpsListSearch[elIdx][intervalIdx].size = dll->getSize();
                insertValue = this->getIntervalValue(intervalIdx);
                searchValue = this->getIntervalValue(intervalIdx);
                mpsListSearch[elIdx][intervalIdx].time += this->countTime([&]() -> void {
                    dll->search(searchValue);
                });
                dll->insertAtEnd(insertValue);
            }
            delete dll;
            dll = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsListSearch);
    this->saveTimeDataToFile("list/mpsListSearch.csv", intervals, mpsListSearch);
    this->deleteMeasurementPointTable(mpsListSearch);
}

void TimeMeasurement::analyzeHeapInsert() {
    MeasurementPoint **mpsHeapInsert = createMeasurementPointTable();
    int key;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsHeapInsert: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            heap = new Heap;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsHeapInsert[i][intervalIdx].size = heap->getSize();
                key = this->getIntervalValue(intervalIdx);
                mpsHeapInsert[i][intervalIdx].time += this->countTime(
                        [&]() -> void { heap->insert(key); });
            }
            delete heap;
            heap = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsHeapInsert);
    this->saveTimeDataToFile("heap/mpsHeapInsert.csv", intervals, mpsHeapInsert);
    this->deleteMeasurementPointTable(mpsHeapInsert);
}

void TimeMeasurement::analyzeHeapRemove() {
    MeasurementPoint **mpsHeapRemove = createMeasurementPointTable();
    int key, randKeyIdx;
    auto *keys = new Table;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsHeapRemove: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            heap = new Heap;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                key = this->getIntervalValue(intervalIdx);
                keys->insertAtEnd(key);
                heap->insert(key);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsHeapRemove[i][intervalIdx].size = heap->getSize();
                randKeyIdx = this->getRand(0, heap->getSize() - 1);
                key = (*keys)[randKeyIdx];
                keys->remove(randKeyIdx);
                mpsHeapRemove[i][intervalIdx].time += this->countTime([&]() -> void {
                    heap->remove(key);
                });
            }
            delete heap;
            heap = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsHeapRemove);
    this->reverseMPS(mpsHeapRemove);
    this->saveTimeDataToFile("heap/mpsHeapRemove.csv", intervals, mpsHeapRemove);
    this->deleteMeasurementPointTable(mpsHeapRemove);
}

void TimeMeasurement::analyzeHeapSearch() {
    MeasurementPoint **mpsHeapSearch = createMeasurementPointTable();
    int insertValue, searchValue;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsHeapSearch: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            heap = new Heap;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                mpsHeapSearch[elIdx][intervalIdx].size = heap->getSize();
                insertValue = this->getIntervalValue(intervalIdx);
                searchValue = this->getIntervalValue(intervalIdx);
                mpsHeapSearch[elIdx][intervalIdx].time += this->countTime([&]() -> void {
                    heap->search(searchValue);
                });
                heap->insert(insertValue);
            }
            delete heap;
            heap = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsHeapSearch);
    this->saveTimeDataToFile("heap/mpsHeapSearch.csv", intervals, mpsHeapSearch);
    this->deleteMeasurementPointTable(mpsHeapSearch);
}

void TimeMeasurement::analyzeRBTInsert() {
    MeasurementPoint **mpsRBTInsert = createMeasurementPointTable();
    int key;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsRBTInsert: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            rbt = new RedBlackTree;
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsRBTInsert[i][intervalIdx].size = rbt->getSize();
                key = this->getIntervalValue(intervalIdx);
                mpsRBTInsert[i][intervalIdx].time += this->countTime(
                        [&]() -> void { rbt->insert(key); });
            }
            delete rbt;
            rbt = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsRBTInsert);
    this->saveTimeDataToFile("rbt/mpsRBTInsert.csv", intervals, mpsRBTInsert);
    this->deleteMeasurementPointTable(mpsRBTInsert);
}

void TimeMeasurement::analyzeRBTRemove() {
    MeasurementPoint **mpsRBTRemove = createMeasurementPointTable();
    int key, randKeyIdx;
    auto *keys = new Table;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsRBTRemove: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            rbt = new RedBlackTree;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                key = this->getIntervalValue(intervalIdx);
                keys->insertAtEnd(key);
                rbt->insert(key);
            }
            for (int i = 0; i < DATA_COUNT; ++i) {
                mpsRBTRemove[i][intervalIdx].size = rbt->getSize();
                randKeyIdx = this->getRand(0, rbt->getSize() - 1);
                key = (*keys)[randKeyIdx];
                keys->remove(randKeyIdx);
                mpsRBTRemove[i][intervalIdx].time += this->countTime([&]() -> void {
                    rbt->remove(key);
                });
            }
            delete rbt;
            rbt = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsRBTRemove);
    this->reverseMPS(mpsRBTRemove);
    this->saveTimeDataToFile("rbt/mpsRBTRemove.csv", intervals, mpsRBTRemove);
    this->deleteMeasurementPointTable(mpsRBTRemove);
}

void TimeMeasurement::analyzeRBTSearch() {
    MeasurementPoint **mpsRBTSearch = createMeasurementPointTable();
    int insertValue, searchValue;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsRBTSearch: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            rbt = new RedBlackTree;
            for (int elIdx = 0; elIdx < DATA_COUNT; ++elIdx) {
                mpsRBTSearch[elIdx][intervalIdx].size = rbt->getSize();
                insertValue = this->getIntervalValue(intervalIdx);
                searchValue = this->getIntervalValue(intervalIdx);
                mpsRBTSearch[elIdx][intervalIdx].time += this->countTime([&]() -> void {
                    rbt->search(searchValue);
                });
                rbt->insert(insertValue);
            }
            delete rbt;
            rbt = nullptr;
        }
        cout << "saved!" << endl;
    }
    this->divideEachTimeByDrawsNumber(mpsRBTSearch);
    this->saveTimeDataToFile("rbt/mpsRBTSearch.csv", intervals, mpsRBTSearch);
    this->deleteMeasurementPointTable(mpsRBTSearch);
}
