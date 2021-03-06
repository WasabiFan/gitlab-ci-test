/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of aruwlib.
 *
 * aruwlib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * aruwlib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with aruwlib.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __PERIODIC_TIMER_HPP__
#define __PERIODIC_TIMER_HPP__

#include "aruwlib/architecture/timeout.hpp"

namespace aruwlib
{
namespace arch
{
/**
 * A timer class which unlike the `Timeout` class will restart when execute
 * is called and returns that the timer has expired. Keeps its expire times
 * aligned with the given timeout period (i.e.: the timeout time will always be a
 * multiple of the period it is constructed to timeout in +/- some constant due to
 * program startup time)
 */
template <typename T>
class PeriodicTimer
{
public:
    PeriodicTimer() : period(0) {}

    explicit PeriodicTimer(uint32_t period) : period(period), timeout(period) {}

    /**
     * Set the timer to expire `period` units of time away from the time at which
     * this function was called.
     */
    inline void restart() { timeout.restart(period); }

    /**
     * Similar to `restart()` but redefine the period of the timer.
     *
     * @param[in] period: the new period to use for this `PeriodicTimer`
     */
    inline void restart(uint32_t period)
    {
        this->period = period;
        restart();
    }

    /**
     * Stop the timer.
     */
    inline void stop() { timeout.stop(); }

    /**
     * Returns `true` on the first call when timer has expired since `restart()`.
     * If timer is checked and has expired, next expiration time is set to the closest
     * time which is an integer product of the `period` away from the time this timer
     * expired.
     *
     * @return `true` the first time the timer has expired (timeout has been reached)
     * since last `restart()`
     */
    inline bool execute()
    {
        if (timeout.execute())
        {
            uint32_t now = T::TimeFunc();

            do
            {
                timeout.expireTime += period;
            } while (timeout.expireTime <= now);

            timeout.isRunning = true;
            timeout.isExecuted = false;
            return true;
        }
        return false;
    }

    /**
     * @return `true` if the timer is stopped
     */
    inline bool isStopped() const { return timeout.isStopped(); }

private:
    uint32_t period;
    T timeout;
};

using PeriodicMilliTimer = PeriodicTimer<MilliTimeout>;
using PeriodicMicroTimer = PeriodicTimer<MicroTimeout>;

}  // namespace arch
}  // namespace aruwlib
#endif
