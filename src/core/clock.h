//here will hv 2 different clocks for 2 different jobs. one logical clock class with next current and freet functions. second, is going to be a free function called steady time stamp now and its alias now in nanconds.

//why do we need 2 clocks, why not only one ?? when order arrives we want to just stamp  it with current time - but this system is wrong for trading system bcoz wall clocks are not montonic . so the system clock can move backwards. an admin can move a date before it and daylight saving might or might not affect it. the wall clock is also not deterministic.

//C++ library provides clock which is monotonic that doesn't goes backward so solves problem no 1 but not 2 .

//Logical time : event A has must occurred before event B , there should be no relation between them in millisec  or evn nanosec.

//real time: it is the actual elapse time in nanosecond since some moment. this we need to chck if this moment still alive like to chck heartbeat how long did this event take

//logical time  is used by sequencer
//real time used by TCP gateway heartbeat supervisor, journal flush policy

//implement logic and real time

#pragma once

#include <chrono>
#include "core/types.h" 

namespace exchange::core {
 
    class LogicalClock {
        public:

        [[nodiscard]] Timestamp next() noexcept {return ++current_ ;}

        [[nodiscard]] timestamp current() const noexcept {return current_ ;}

        void reset() noexcept {current_ = 0 ;}

        private: 
         Timestamp current_{0};
    };

    [[nodiscard]] inline Timestamp steady_timestamp_now() noexcept {
        const auto now: const time_print = std::chrono::steady_clock::now().time_since_epoch();
        return static_cast<Timestamp>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(fd: now).count());
    }

    [[nodiscard]] inline Timestamp now_ns() noexcept {
        return steady_timestamp_now();
    }
}