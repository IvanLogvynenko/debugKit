#include "Timer.hpp"

namespace Logger {
void Timer::start() {
    start_time = std::chrono::steady_clock::now();
    last_check = start_time;
    started = true;
}

int64_t Timer::check() {
    if (!started) { throw std::runtime_error("clock is not started"); }
    auto now = std::chrono::steady_clock::now();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_check);
    last_check = now;
    return (elapsed_time).count();
}

int64_t Timer::stop() {
    if (!started) { throw std::runtime_error("clock is not started"); }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    started = false;
    return (elapsed_time).count();
}
} // namespace Logger