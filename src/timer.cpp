#include "../include/timer.h"

time_start // NOLINT
time_end // NOLINT


void Timer::start() {
    start_time = high_resolution_clock::now();
}

void Timer::stop() {
    stop_time = high_resolution_clock::now();
}

float Timer::getTime() {
    return (float) (duration_cast<milliseconds>(stop_time - start_time).count()) / 1000;
}

float Timer::getCurrentTime() {
    time_point_t current_time = high_resolution_clock::now();
    return (float) (duration_cast<milliseconds>(current_time - start_time).count()) / 1000;
}




