// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TIMESPAN_HPP
#define SCENER_TIMESPAN_HPP

#include <cstdlib>
#include <chrono>
#include <cstdint>
#include <ratio>

namespace scener {

/// Represents a time interval.
class timespan final
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
    /// Represents the number of ticks in 1 day.
    constexpr static const std::int64_t ticks_per_day = 864000000000;

    /// Represents the number of ticks in 1 hour.
    constexpr static const std::int64_t ticks_per_hour = 36000000000;

    /// Represents the number of ticks in 1 millisecond.
    constexpr static const std::int64_t ticks_per_millisecond = 10000;

    /// Represents the number of ticks in 1 minute.
    constexpr static const std::int64_t ticks_per_minute = 600000000;

    /// Represents the number of ticks in 1 second.
    constexpr static const std::int64_t ticks_per_second = 10000000;

public:
    /// Represents the maximum TimeSpan value.
    constexpr static const timespan max_value()
    {
        return { std::numeric_limits<std::int64_t>::max() };
    }

    /// Represents the minimum TimeSpan value.
    constexpr static const timespan min_value()
    {
        return { std::numeric_limits<std::int64_t>::min() };
    }

    /// Represents the zero TimeSpan value. This field is read-only.
    constexpr static const timespan zero()
    {
        return { 0 };
    }

    /// Returns a TimeSpan that represents a specified number of days.
    /// \param value a number of days, accurate to the nearest millisecond.
    /// \returns a TimeSpan that represents a specified number of days.
    constexpr static timespan from_days(double value) noexcept
    {
        return { std::chrono::duration_cast<ticks_duration>(days_duration(value)).count() };
    }

    /// Returns a TimeSpan that represents a specified duration.
    /// \param value a duration.
    /// \returns a TimeSpan that represents a specified duration.
    constexpr static timespan from_duration(const timespan::clock::duration& value) noexcept
    {
        return { std::chrono::duration_cast<ticks_duration>(value).count() };
    }

    /// Returns a TimeSpan that represents a specified number of hours.
    /// \param value a number of hours, accurate to the nearest millisecond.
    /// \returns a TimeSpan that represents a specified number of days.
    constexpr static timespan from_hours(double value) noexcept
    {
        return { std::chrono::duration_cast<ticks_duration>(hours_duration(value)).count() };
    }

    /// Returns a TimeSpan that represents a specified number of milliseconds.
    /// \param value a number of milliseconds.
    /// \returns a TimeSpan that represents a specified number of milliseconds.
    constexpr static timespan from_milliseconds(double value) noexcept
    {
        return { std::chrono::duration_cast<ticks_duration>(milli_seconds_duration(value)).count() };
    }

    /// Returns a TimeSpan that represents a specified number of minutes.
    /// \param value a number of minutes, accurate to the nearest millisecond.
    /// \returns a TimeSpan that represents a specified number of minutes.
    constexpr static timespan from_minutes(double value) noexcept
    {
        return { std::chrono::duration_cast<ticks_duration>(minutes_duration(value)).count() };
    }

    /// Returns a TimeSpan that represents a specified number of seconds.
    /// \param value a number of seconds, accurate to the nearest millisecond.
    /// \returns a TimeSpan that represents a specified number of seconds.
    constexpr static timespan from_seconds(double value) noexcept
    {
        return { std::chrono::duration_cast<ticks_duration>(seconds_duration(value)).count() };
    }

    /// Returns a TimeSpan that represents a specified time.
    /// \param value a number of ticks that represent a time.
    /// \returns a TimeSpan that represents a specified time.
    constexpr static timespan from_ticks(std::int64_t value) noexcept
    {
        return { value };
    }

public:
    /// Initializes a new instance of the TimeSpan class with the given ticks value.
    /// \param ticks a time period expressed in ticks.
    constexpr timespan(std::int64_t ticks) noexcept
        : _ticks { ticks }
    {
    }

    /// Initializes a new instance of the TimeSpan class with the given hours, minutes and seconds.
    /// \param hours number of hours.
    /// \param minutes number of minutes.
    /// \param seconds number of seconds.
    constexpr timespan(std::int32_t hours, std::int32_t minutes, std::int32_t seconds) noexcept
        : timespan { 0, hours, minutes, seconds, 0 }
    {
    }

    /// Initializes a new instance of the TimeSpan class with the given days, hours, minutes and seconds.
    /// \param days number of days.
    /// \param hours number of hours.
    /// \param minutes number of minutes.
    /// \param seconds number of seconds.
    constexpr timespan(std::int32_t days, std::int32_t hours, std::int32_t minutes, std::int32_t seconds) noexcept
        : timespan { days, hours, minutes, seconds, 0 }
    {
    }

    /// Initializes a new instance of the TimeSpan class with the given days, hours, minutes, seconds and milliseconds.
    /// \param days number of days.
    /// \param hours number of hours.
    /// \param minutes number of minutes.
    /// \param seconds number of seconds.
    /// \param milliseconds number of milliseconds.
    constexpr timespan(std::int32_t days
                      , std::int32_t hours
                      , std::int32_t minutes
                      , std::int32_t seconds
                      , std::int32_t milliseconds) noexcept
        : _ticks { std::chrono::duration_cast<ticks_duration>(days_duration(days))
                 + std::chrono::duration_cast<ticks_duration>(hours_duration(hours))
                 + std::chrono::duration_cast<ticks_duration>(minutes_duration(minutes))
                 + std::chrono::duration_cast<ticks_duration>(seconds_duration(seconds))
                 + std::chrono::duration_cast<ticks_duration>(milli_seconds_duration(milliseconds)) }
    {
    }

public:
    /// Returns a new TimeSpan object whose value is the absolute value of this instance.
    /// \returns a new TimeSpan object whose value is the absolute value of this instance.
    inline timespan duration() const noexcept
    {
        return { std::abs(_ticks.count()) };
    }

    /// Returns a new TimeSpan object whose value is the negated value of this instance.
    /// \returns a new TimeSpan object whose value is the negated value of this instance.
    constexpr timespan negate() const noexcept
    {
        return { -_ticks.count() };
    }

    //// Gets the days component of the time interval represented by the current TimeSpan.
    /// \returns the days component of the time interval represented by the current TimeSpan.
    constexpr std::int32_t days() const noexcept
    {
        return (_ticks.count() / ticks_per_day);
    }

    /// Gets the hours component of the time interval represented by the current TimeSpan.
    /// \returns the hours component of the time interval represented by the current TimeSpan.
    constexpr std::int32_t hours() const noexcept
    {
        return (_ticks.count() % ticks_per_day / ticks_per_hour);
    }

    /// Gets the milliseconds component of the time interval represented by the current TimeSpan.
    /// \returns the milliseconds component of the time interval represented by the current TimeSpan.
    constexpr std::int32_t milli_seconds() const noexcept
    {
        return (_ticks.count() % ticks_per_second / ticks_per_millisecond);
    }

    /// Gets the minutes component of the time interval represented by the current TimeSpan.
    /// \returns the minutes component of the time interval represented by the current TimeSpan.
    constexpr std::int32_t minutes() const noexcept
    {
        return (_ticks.count() % ticks_per_hour / ticks_per_minute);
    }

    /// Gets the seconds component of the time interval represented by the current TimeSpan.
    /// \returns the seconds component of the time interval represented by the current TimeSpan.
    constexpr std::int32_t seconds() const noexcept
    {
        return (_ticks.count() % ticks_per_minute / ticks_per_second);
    }

    /// Gets the number of ticks that represent the value of the current TimeSpan.
    /// \returns the number of ticks that represent the value of the current TimeSpan.
    constexpr std::int64_t ticks() const noexcept
    {
        return _ticks.count();
    }

    /// Gets the value of the current TimeSpan structure expressed in whole and fractional days.
    /// \return Gets the value of the current TimeSpan structure expressed in whole and fractional days.
    constexpr double total_days() const noexcept
    {
        return std::chrono::duration_cast<days_duration>(_ticks).count();
    }

    /// Gets the value of the current TimeSpan structure expressed in whole and fractional hours.
    /// \returns the value of the current TimeSpan structure expressed in whole and fractional hours.
    constexpr double total_hours() const noexcept
    {
        return std::chrono::duration_cast<hours_duration>(_ticks).count();
    }

    /// Gets the value of the current TimeSpan structure expressed in whole and fractional milliseconds.
    /// \returns the value of the current TimeSpan structure expressed in whole and fractional milliseconds.
    constexpr double total_milli_seconds() const noexcept
    {
        return std::chrono::duration_cast<milli_seconds_duration>(_ticks).count();
    }

    /// Gets the value of the current TimeSpan structure expressed in whole and fractional minutes.
    /// \returns the value of the current TimeSpan structure expressed in whole and fractional minutes.
    constexpr double total_minutes() const noexcept
    {
        return std::chrono::duration_cast<minutes_duration>(_ticks).count();
    }

    /// Gets the value of the current TimeSpan structure expressed in whole and fractional seconds.
    /// \returns the value of the current TimeSpan structure expressed in whole and fractional seconds.
    constexpr double total_seconds() const noexcept
    {
        return std::chrono::duration_cast<seconds_duration>(_ticks).count();
    }

    /// Returns a TimeSpan that represents a specified duration type.
    /// \returns a TimeSpan that represents a specified duration type.
    template <class _Duration>
    constexpr timespan::clock::duration to_duration() const noexcept
    {
        return std::chrono::duration_cast<_Duration>(_ticks);
    }

public:
    /// Equality operator for comparing TimeSpan instances.
    constexpr bool operator==(const timespan& t2) const noexcept
    {
        return (_ticks == t2._ticks);
    }

    /// Inequality operator for comparing TimeSpan instances.
    constexpr bool operator!=(const timespan& t2) const noexcept
    {
        return !(*this == t2);
    }

    constexpr bool operator>(const timespan& t2) const noexcept
    {
        return (_ticks > t2._ticks);
    }

    constexpr bool operator>=(const timespan& t2) const noexcept
    {
        return (_ticks >= t2._ticks);
    }

    constexpr bool operator<(const timespan& t2) const noexcept
    {
        return (_ticks < t2._ticks);
    }

    constexpr bool operator<=(const timespan& t2) const noexcept
    {
        return (_ticks <= t2._ticks);
    }

    constexpr timespan& operator-=(const timespan& t2) noexcept
    {
        _ticks -= t2._ticks;

        return *this;
    }

    constexpr timespan& operator+=(const timespan& t2) noexcept
    {
        _ticks += t2._ticks;

        return *this;
    }

    constexpr const timespan operator-(const timespan& t2) const noexcept
    {
        auto result = *this;

        result -= t2;

        return result;
    }

    constexpr const timespan operator+(const timespan& t2) const noexcept
    {
        auto result = *this;

        result += t2;

        return result;
    }

private:
    timespan::ticks_duration _ticks;
};

}

#endif // SCENER_TIMESPAN_HPP
