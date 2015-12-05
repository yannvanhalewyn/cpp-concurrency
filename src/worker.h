#ifndef __WORKER_H__
#define __WORKER_H__

// A simple worker struct which simply holds the pointer to the output and the
// thread reference.
typedef struct Worker {
    long* output = new long(0);
    std::thread* thread = nullptr;

    ~Worker() {
        delete this->output;
        if (this->thread != nullptr) {
            delete this->thread;
        }
    }
} Worker;

#endif
