#include "stopwatch.h"
#include "iostream"

void Stopwatch::begin() {
    m_start = std::chrono::high_resolution_clock::now();
}

void Stopwatch::end() {
    m_end = std::chrono::high_resolution_clock::now();
}

double Stopwatch::getElapsedTime() {
    std::chrono::duration<double, std::milli> elapsed = m_end - m_start;
    return elapsed.count();
}
