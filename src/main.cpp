#include <iostream>
#include <thread>
#include <vector>
#include "stopwatch.h"
#include "worker.h"

#define DEFAULT 500000000 // 5 * 10^8

// The function we want to stresstest!
void sum(long from, long to, long* out) {
    if (from > to) throw "Please give arguments in ascending order";
    long sum = 0;
    for (long i = from; i <= to; i++) { sum += i; }
    *out = sum;
}

long splitLoadIntoWorkersAndWait(long load, int numWorkers) {
    std::vector<Worker*> workers;

    // Split of workers each having a chunk of the payload
    for (int i = 0; i < numWorkers; ++i) {
        long from = (i * load / numWorkers) + 1;
        long to = (i + 1) * load / numWorkers;
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
void test(long load, int numWorkers) {
    std::cout << "Running a test with " << numWorkers << " threads."
        << std::endl;
    Stopwatch* timer = new Stopwatch();
    timer->begin();
    long result = splitLoadIntoWorkersAndWait(load, numWorkers);
    timer->end();
    std::cout << "The solution is: " << result << std::endl;
    std::cout << "Elapsed time: " << timer->getElapsedTime() << "ms"
        << std::endl << std::endl;
}

// Running our tests
int main(int argc, char *argv[])
{
    long load = DEFAULT;
    if (argc == 2)
        load = std::stol(argv[1]);

    std::cout << "Running tests for a load of " << load << std::endl;

    test(load, 1);
    test(load, 2);
    test(load, 4);
    test(load, 8);
    test(load, 16);
    return 0;
}
