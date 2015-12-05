#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include <chrono>

class Stopwatch
{
public:
    Stopwatch () {}
    void begin();
    void end();
    double getElapsedTime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};



#endif
