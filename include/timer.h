#ifndef DA_T1_TIMER_H
#define DA_T1_TIMER_H

#include <chrono>

using namespace std::chrono;
using namespace std;

#define time_start high_resolution_clock::time_point Timer::start_time;
#define time_end high_resolution_clock::time_point Timer::stop_time;

typedef high_resolution_clock::time_point time_point_t;

class Timer {
private:
    static time_point_t start_time, stop_time;
public:
    static void start();

    static void stop();

    static float getCurrentTime();

    static float getTime();
};

#endif //DA_T1_TIMER_H
