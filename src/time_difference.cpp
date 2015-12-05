#include "time_difference.h"
#include "iostream"

void TimeDifference::begin() {
    m_start = std::chrono::high_resolution_clock::now();
}

void TimeDifference::end() {
    m_end = std::chrono::high_resolution_clock::now();
}

double TimeDifference::getElapsedTime() {
    std::chrono::duration<double, std::milli> elapsed = m_end - m_start;
    return elapsed.count();
}
