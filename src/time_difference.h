#ifndef __TIME_DIFFERENCE_H__
#define __TIME_DIFFERENCE_H__

#include <chrono>

class TimeDifference
{
public:
    TimeDifference () {}
    void begin();
    void end();
    double getElapsedTime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};



#endif
