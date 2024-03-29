#ifndef OMEGA_UTIL_TIME_HPP
#define OMEGA_UTIL_TIME_HPP

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::util {

class Time {
  public:
    static void init() {
        start = std::chrono::high_resolution_clock::now();
    }

    /**
     * @return the time since the initialization of the engine in milliseconds
     */
    template <typename T>
    static T get_time_millis() {
        return static_cast<T>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - start)
                .count() * 0.001 * 0.001);
    }

    /**
     * @return the time since the initialization of the engine in seconds
     */
    template <typename T>
    static T get_time() {
        return static_cast<T>(get_time_millis<double>() * 0.001);
    }

    /**
     * Add a time event to be tracked
     * @param seconds
     * @param callback is called when the timer completes,
     * passes the elapsed time since the timer ended
     */
    static void add_timer(f32 seconds, std::function<void(f32)> callback) {
        // create new event
        uptr<TimeEvent> time_event = create_uptr<TimeEvent>();
        time_event->duration = seconds;
        time_event->callback = callback;
        // add the new timer
        timers.push_back(std::move(time_event));
    }

    /**
     * Step the timers, call the callback if the timer is complete,
     * and delete the timer event
     * @param dt delta time
     */
    static void tick(f32 dt) {
        // iterate in reverse all the events
        for (int i = timers.size() - 1; i >= 0; --i) {
            TimeEvent &event = *timers[(size_t)i];
            event.timer += dt;
            // if the timer is completed, call the callback function
            if (event.timer >= event.duration) {
                if (event.callback != nullptr) {
                    event.callback(event.timer - event.duration);
                }
                // delete the event now that it's complete
                // std::move(timers[(size_t)i]);
                timers.erase(timers.begin() + i);
            }
        }
    }

    /**
     * Sleep the current thread for specified time
     * @param time seconds
     */
    template <typename T>
    static void sleep(T time) {
        std::this_thread::sleep_for(
            std::chrono::microseconds((i64)(time * 1000.0 * 1000.0)));
    }

    /**
     * @return the current time formatted as such: Day-of-week Month Day hr:min:sec yr
     */
    static std::string get_current_time() {
        std::time_t current_time = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        return std::string(
            std::ctime(&current_time));
    }

  private:
    struct TimeEvent {
        f32 timer = 0.0f;
        f32 duration = 0.0f;
        std::function<void(f32)> callback = nullptr;
    };

    static std::vector<uptr<TimeEvent>> timers;
    static std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

} // namespace omega::util

#endif // OMEGA_UTIL_TIME_HPP
