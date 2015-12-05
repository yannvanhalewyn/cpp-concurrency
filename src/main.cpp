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
    // Single Threaded
    std::cout << "Running single threaded example: " << std::endl;
    TimeDifference* timer = new TimeDifference();
    timer->begin();
    long *out = new long;
    sum(0, numberToSumUp, out);
    timer->end();
    std::cout << "Solution: " << *out << std::endl;
    std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl << std::endl;
    delete timer;

    // Multithreaded
    std::cout << "Running example with 2 threads" << std::endl;
    timer = new TimeDifference();
    timer->begin();

    long* out1 = new long;
    long* out2 = new long;
    std::thread t1(sum, 0, numberToSumUp/2, out1);
    std::thread t2(sum, numberToSumUp/2 + 1, numberToSumUp, out2);
    t1.join();
    t2.join();

    std::cout << "Solution: " << *out1 + *out2 << std::endl;
    timer->end();
    std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl << std::endl;
    delete timer;

    // 3 threads
    std::cout << "Running example with 3 threads" << std::endl;
    timer = new TimeDifference();
    timer->begin();

    long* out4 = new long;
    long* out5 = new long;
    long* out6 = new long;
    std::thread t4(sum, 0, numberToSumUp/3, out4);
    std::thread t5(sum, numberToSumUp/3 + 1, 2 * numberToSumUp/3, out5);
    std::thread t6(sum, 2 * numberToSumUp/3 + 1, numberToSumUp, out6);
    t4.join();
    t5.join();
    t6.join();

    std::cout << "Solution: " << *out4 + *out5 + *out6 << std::endl;
    timer->end();
    std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl;
    return 0;
}
