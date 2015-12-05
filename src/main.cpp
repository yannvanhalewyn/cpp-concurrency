#include <iostream>
#include <future>
#include <vector>
#include "time_difference.h"

const int THE_NUMBER = 100000000; // 10^7

// The function we want to stresstest!
void sum(int from, int to, long* out) {
    if (from > to) throw "Please give arguments in ascending order";

    long sum = 0;

    for (int i = from; i <= to; i++) {
        sum += i;
    }

    *out = sum;
}

// A simple worker struct which simply holds the pointer to the output and the
// thread reference.
typedef struct Worker {
    long* output = new long(0);
    std::thread* thread = nullptr;

    Worker() { std::cout << "Creating worker " << this << std::endl; }
    ~Worker() {
        delete this->output;
        if (this->thread != nullptr) {
            delete this->thread;
        }
    }
} Worker;

long splitSumIntoWorkersAndWait(int numToSum, int numWorkers) {
    std::vector<Worker*> workers;

    // Split of workers each having a chunk of the payload
    for (int i = 0; i < numWorkers; ++i) {
        int from = (i * numToSum / numWorkers) + 1;
        int to = (i + 1) * numToSum / numWorkers;
        Worker* w = new Worker;
        w->thread = new std::thread(sum, from, to, w->output);
        workers.push_back(w);
    }

    // Join all workers and store al the return values
    long ret = 0;
    for (Worker* w : workers) {
        w->thread->join();
        ret += *w->output;
        delete w;
    }

    return ret;
}

// calls the splitAndWait function and timebenches it.
void test(int number, int numWorkers) {
    std::cout << "Running a test with " << numWorkers << " threads." << std::endl;
    TimeDifference* timer = new TimeDifference();
    timer->begin();
    long result = splitSumIntoWorkersAndWait(number, numWorkers);
    timer->end();
    std::cout << "The solution is: " << result << std::endl;
    std::cout << "Elapsed time: " << timer->getElapsedTime() << "ms" << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
    test(THE_NUMBER, 1);
    test(THE_NUMBER, 2);
    test(THE_NUMBER, 4);
    test(THE_NUMBER, 8);
    test(THE_NUMBER, 16);
    return 0;
}
