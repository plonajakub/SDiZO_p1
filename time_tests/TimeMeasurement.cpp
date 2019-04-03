#include "TimeMeasurement.h"

TimeMeasurement::TimeMeasurement() : table(nullptr), dll(nullptr), heap(nullptr), rbt(nullptr) {
}

void TimeMeasurement::run() {
    MeasurementPoint mpsTableInsertBeg[DATA_COUNT][INTERVALS_OF_VALUES] = {{}};
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "mpsTableInsertBeg: draw No. " + std::to_string(draw) + "...";
        for (int intervalIdx = 0; intervalIdx < INTERVALS_OF_VALUES; ++intervalIdx) {
            delete table;
            table = new Table;
            for (auto &intervalsData : mpsTableInsertBeg) {
                intervalsData[intervalIdx].size = table->getSize();
                switch (intervalIdx) {
                    case 0:
                        intervalsData[intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(0, INT_MAX / 2)); });
                        break;
                    case 1:
                        intervalsData[intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(INT_MAX / 2, INT_MAX)); });
                        break;
                    case 2:
                        intervalsData[intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(0, INT_MAX)); });
                        break;
                    case 3:
                        intervalsData[intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(0, 100)); });
                        break;
                    case 4:
                        intervalsData[intervalIdx].time += this->countTime(
                                [&]() -> void { table->insertAtStart(this->getRand(INT_MAX - 100, INT_MAX)); });
                        break;
                    default:
                        throw std::exception();
                }
            }
        }
        cout << "saved!" << endl;
    }
    for (auto &row : mpsTableInsertBeg) {
        for (auto &el : row) {
            el.time /= DRAWS_NUMBER;
        }
    }
    this->saveTimeDataToFile("mpsTableInsertBeg.csv", intervals, mpsTableInsertBeg);
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
                                    const MeasurementPoint (&measurementPoints)[DATA_COUNT][INTERVALS_OF_VALUES]) {
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

    for (const auto &row : measurementPoints) {
        for (int i = 0; i < INTERVALS_OF_VALUES - 1; ++i) {
            if (row[i].size != row[i + 1].size) {
                throw std::exception();
            }
        }
        file << row[0].size;
        for (const auto &element : row) {
            file << sep << element.time;
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