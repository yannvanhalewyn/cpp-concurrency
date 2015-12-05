#include <iostream>
#include <future>
#include "time_difference.h"

const int numberToSumUp = 10000000; // 10^7

void sum(int from, int to, long* out) {
    if (from > to) throw "Please give arguments in ascending order";

    long sum = 0;

    for (int i = from; i <= to; i++) {
        sum += i;
    }
    *out = sum;
}

int main(int argc, char *argv[])
{
    // Multithreaded
    std::cout << "Running example with 2 threads" << std::endl;
    TimeDifference* timer = new TimeDifference();
    timer->begin();


    long* out1 = new long;
    long* out2 = new long;

    std::thread t1(sum, 0, numberToSumUp/2, out1);
    std::thread t2(sum, numberToSumUp/2 + 1, numberToSumUp, out2);

    t1.join();
    t2.join();

    std::cout << "Solution: " << *out1 + *out2 << std::endl;

    timer->end();

    std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl;
    return 0;
}
