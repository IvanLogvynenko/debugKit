#pragma once

#include <chrono>
#include <stdexcept>

class Timer {
protected:
    bool started = false;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point last_check;
public:
    /// @brief Starts the timer
    void start();
    /// @brief Ret elepsed time from last check, without stopping clock
    int64_t check();
    /// @brief Get elepsed time, stopping clock
    int64_t stop();
    /// @brief Check if the timer is started
    inline bool isStarted() { return started; }
};