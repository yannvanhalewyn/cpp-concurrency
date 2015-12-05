#include <iostream>
#include <future>
#include <vector>
#include "time_difference.h"

const int THE_NUMBER = 10000000; // 10^7

void sum(int from, int to, long* out) {
    if (from > to) throw "Please give arguments in ascending order";

    long sum = 0;

    for (int i = from; i <= to; i++) {
        sum += i;
    }

    *out = sum;
}

long splitSumIntoWorkersAndWait(int numToSum, int numWorkers) {
    std::vector<std::thread*> threads;
    std::vector<long*> outputs;

    for (int i = 0; i < numWorkers; i++) {
        long* out = new long;
        outputs.push_back(out);
        int from = (i * numToSum / numWorkers) + 1;
        int to = (i + 1) * numToSum / numWorkers;
        threads.push_back(new std::thread(sum, from, to, out));
    }

    for (std::thread* t : threads) {
        std::cout << "joined" << std::endl;
        t->join();
        delete t;
    }

    for (long* output : outputs) {
        std::cout << *output << std::endl;
    }
}

int main(int argc, char *argv[])
{
    splitSumIntoWorkersAndWait(THE_NUMBER, 4);
    // // Single Threaded
    // std::cout << "Running single threaded example: " << std::endl;
    // TimeDifference* timer = new TimeDifference();
    // timer->begin();
    // long *out = new long;
    // sum(0, numberToSumUp, out);
    // timer->end();
    // std::cout << "Solution: " << *out << std::endl;
    // std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl << std::endl;
    // delete timer;
    //
    // // Multithreaded
    // std::cout << "Running example with 2 threads" << std::endl;
    // timer = new TimeDifference();
    // timer->begin();
    //
    // long* out1 = new long;
    // long* out2 = new long;
    // std::thread t1(sum, 0, numberToSumUp/2, out1);
    // std::thread t2(sum, numberToSumUp/2 + 1, numberToSumUp, out2);
    // t1.join();
    // t2.join();
    //
    // std::cout << "Solution: " << *out1 + *out2 << std::endl;
    // timer->end();
    // std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl << std::endl;
    // delete timer;
    //
    // // 3 threads
    // std::cout << "Running example with 3 threads" << std::endl;
    // timer = new TimeDifference();
    // timer->begin();
    //
    // long* out4 = new long;
    // long* out5 = new long;
    // long* out6 = new long;
    // std::thread t4(sum, 0, numberToSumUp/3, out4);
    // std::thread t5(sum, numberToSumUp/3 + 1, 2 * numberToSumUp/3, out5);
    // std::thread t6(sum, 2 * numberToSumUp/3 + 1, numberToSumUp, out6);
    // t4.join();
    // t5.join();
    // t6.join();
    //
    // std::cout << "Solution: " << *out4 + *out5 + *out6 << std::endl;
    // timer->end();
    // std::cout << "Time elapsed: " << timer->getElapsedTime() << "ms" << std::endl;
    return 0;
}
