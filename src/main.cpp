#include <iostream>
#include <thread>
#include "time_difference.h"

const int numberToSumUp = 1000000;

int sum(int from = 0, int to = 0) {
    if (from > to) throw "Please give arguments in ascending order";

    int sum = 0;

    for (int i = from; i <= to; i++) {
        sum += i;
    }

    return sum;
}

int main(int argc, char *argv[])
{
    TimeDifference* t = new TimeDifference();
    t->begin();

    std::cout << "Solution: " << sum(0, numberToSumUp) << std::endl;

    t->end();

    std::cout << "Time elapsed: " << t->getElapsedTime() << "ms" << std::endl;
    return 0;
}
