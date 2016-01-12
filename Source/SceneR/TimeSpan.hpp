// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TIMESPAN_HPP
#define SCENER_TIMESPAN_HPP

#include <chrono>
#include <cstdint>
#include <ratio>

namespace SceneR {

/**
 * Represents a time interval.
 */
struct TimeSpan final
{
public:
    using clock                  = std::chrono::high_resolution_clock;
    using days_duration          = std::chrono::duration<double      , std::ratio<86400>>;
    using hours_duration         = std::chrono::duration<double      , std::ratio<3600>>;
    using minutes_duration       = std::chrono::duration<double      , std::ratio<60>>;
    using seconds_duration       = std::chrono::duration<double>;
    using milli_seconds_duration = std::chrono::duration<double      , std::ratio<1, 1000>>;
    using micro_seconds_duration = std::chrono::duration<double      , std::ratio<1, 1000000>>;
    using ticks_duration         = std::chrono::duration<std::int64_t, std::ratio<1, 10000000>>;

public:
    /**
     * Represents the maximum TimeSpan value.
     */
    static const TimeSpan max_value;

    /**
     * Represents the minimum TimeSpan value.
     */
    static const TimeSpan min_value;

    /**
     * Represents the number of ticks in 1 day.
     */
    constexpr static const std::int64_t ticks_per_day = 864000000000;

    /**
     * Represents the number of ticks in 1 hour.
     */
    constexpr static const std::int64_t ticks_per_hour = 36000000000;

    /**
     * Represents the number of ticks in 1 millisecond.
     */
    constexpr static const std::int64_t ticks_per_millisecond = 10000;

    /**
     * Represents the number of ticks in 1 minute.
     */
    constexpr static const std::int64_t ticks_per_minute = 600000000;

    /**
     * Represents the number of ticks in 1 second.
     */
    constexpr static const std::int64_t ticks_per_second = 10000000;

    /**
     * Represents the zero TimeSpan value. This field is read-only.
     */
    static const TimeSpan zero;

public:
    /**
     * Returns a TimeSpan that represents a specified number of days.
     */
    static TimeSpan from_days(double value) noexcept;

    /**
     * Returns a TimeSpan that represents a specified duration.
     */
    static TimeSpan from_duration(const TimeSpan::clock::duration& value) noexcept;

    /**
     * Returns a TimeSpan that represents a specified number of hours.
     */
    static TimeSpan from_hours(double value) noexcept;

    /**
     * Returns a TimeSpan that represents a specified number of milliseconds.
     */
    static TimeSpan from_milliseconds(double value) noexcept;

    /**
     * Returns a TimeSpan that represents a specified number of minutes.
     */
    static TimeSpan from_minutes(double value) noexcept;

    /**
     * Returns a TimeSpan that represents a specified number of seconds.
     */
    static TimeSpan from_seconds(double value) noexcept;

    /**
     * Returns a TimeSpan that represents a specified time.
     */
    static TimeSpan from_ticks(std::int64_t value) noexcept;

public:
    /**
     * Initializes a new instance of the TimeSpan class with the given ticks value.
     */
    TimeSpan(std::int64_t ticks) noexcept;

    /**
     * Initializes a new instance of the TimeSpan class with the given hours, minutes and seconds.
     */
    TimeSpan(std::int32_t hours, std::int32_t minutes, std::int32_t seconds) noexcept;

    /**
     * Initializes a new instance of the TimeSpan class with the given days, hours, minutes and seconds.
     */
    TimeSpan(std::int32_t days, std::int32_t hours, std::int32_t minutes, std::int32_t seconds) noexcept;

    /**
     * Initializes a new instance of the TimeSpan class with the given days, hours, minutes, seconds and milliseconds.
     */
    TimeSpan(std::int32_t days
           , std::int32_t hours
           , std::int32_t minutes
           , std::int32_t seconds
           , std::int32_t milliseconds) noexcept;

    /**
     * Initializes a new instance of the TimeSpan class with the given timespan.
     */
    TimeSpan(const TimeSpan& interval) = default;

    /**
     * Releases all resources being used by this TimeSpan.
     */
    ~TimeSpan() = default;

public:
    /**
     * Returns a new TimeSpan object whose value is the absolute value of this instance.
     */
    TimeSpan duration() const noexcept;

    /**
     * Returns a new TimeSpan object whose value is the negated value of this instance.
     */
    TimeSpan negate() const noexcept;

    /**
     * Gets the days component of the time interval represented by the current TimeSpan structure.
     */
    std::int32_t days() const noexcept;

    /**
     * Gets the hours component of the time interval represented by the current TimeSpan structure.
     */
    std::int32_t hours() const noexcept;

    /**
     * Gets the milliseconds component of the time interval represented by the current TimeSpan structure.
     */
    std::int32_t milli_seconds() const noexcept;

    /**
     * Gets the minutes component of the time interval represented by the current TimeSpan structure.
     */
    std::int32_t minutes() const noexcept;

    /**
     * Gets the seconds component of the time interval represented by the current TimeSpan structure.
     */
    std::int32_t seconds() const noexcept;

    /**
     * Gets the number of ticks that represent the value of the current TimeSpan structure.
     */
    std::int64_t ticks() const noexcept;

    /**
     * Gets the value of the current TimeSpan structure expressed in whole and fractional days.
     */
    double total_days() const noexcept;

    /**
     * Gets the value of the current TimeSpan structure expressed in whole and fractional hours.
     */
    double total_hours() const noexcept;

    /**
     * Gets the value of the current TimeSpan structure expressed in whole and fractional milliseconds.
     */
    double total_milli_seconds() const noexcept;

    /**
     * Gets the value of the current TimeSpan structure expressed in whole and fractional minutes.
     */
    double total_minutes() const noexcept;

    /**
     * Gets the value of the current TimeSpan structure expressed in whole and fractional seconds.
     */
    double total_seconds() const noexcept;

    /**
     * Returns a TimeSpan that represents a specified duration type.
     */
    template <class _Duration>
    inline TimeSpan::clock::duration to_duration() const noexcept
    {
        return std::chrono::duration_cast<_Duration>(_ticks);
    }

public:
    TimeSpan& operator=(const TimeSpan& t2) = default;

    bool operator==(const TimeSpan& t2) const noexcept;
    bool operator!=(const TimeSpan& t2) const noexcept;
    bool operator>(const TimeSpan& t2) const noexcept;
    bool operator>=(const TimeSpan& t2) const noexcept;
    bool operator<(const TimeSpan& t2) const noexcept;
    bool operator<=(const TimeSpan& t2) const noexcept;
    TimeSpan& operator-=(const TimeSpan& t2) noexcept;
    TimeSpan& operator+=(const TimeSpan& t2) noexcept;
    const TimeSpan operator-(const TimeSpan& t2) const noexcept;
    const TimeSpan operator+(const TimeSpan& t2) const noexcept;

private:
    TimeSpan::ticks_duration _ticks;
};

}

#endif // SCENER_TIMESPAN_HPP
