// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <chrono>
#include <ratio>

#include <System/Core.hpp>

namespace System
{
    /**
     * Represents a time interval.
     */
    struct TimeSpan
    {
    public:
        using Clock                = std::chrono::high_resolution_clock;
        using DaysDuration         = std::chrono::duration<System::Double, std::ratio<86400>>;
        using HoursDuration        = std::chrono::duration<System::Double, std::ratio<3600>>;
        using MinutesDuration      = std::chrono::duration<System::Double, std::ratio<60>>;
        using SecondsDuration      = std::chrono::duration<System::Double>;
        using MillisecondsDuration = std::chrono::duration<System::Double, std::ratio<1, 1000>>;
        using MicrosecondsDuration = std::chrono::duration<System::Double, std::ratio<1, 1000000>>;
        using TicksDuration        = std::chrono::duration<int64_t       , std::ratio<1, 10000000>>;

    public:
        /**
         * Represents the maximum TimeSpan value.
         */
        static const TimeSpan MaxValue;

        /**
         * Represents the minimum TimeSpan value.
         */
        static const TimeSpan MinValue;

        /**
         * Represents the number of ticks in 1 day.
         */
        constexpr static const int64_t TicksPerDay = 864000000000;

        /**
         * Represents the number of ticks in 1 hour.
         */
        constexpr static const int64_t TicksPerHour = 36000000000;

        /**
         * Represents the number of ticks in 1 millisecond.
         */
        constexpr static const int64_t TicksPerMillisecond = 10000;

        /**
         * Represents the number of ticks in 1 minute.
         */
        constexpr static const int64_t TicksPerMinute = 600000000;

        /**
         * Represents the number of ticks in 1 second.
         */
        constexpr static const int64_t TicksPerSecond = 10000000;

        /**
         * Represents the zero TimeSpan value. This field is read-only.
         */
        static const TimeSpan Zero;

    public:
        /**
         * Returns a TimeSpan that represents a specified number of days.
         */
        static TimeSpan FromDays(const System::Double& value);

        /**
         * Returns a TimeSpan that represents a specified duration.
         */
        static TimeSpan FromDuration(const TimeSpan::Clock::duration& value);

        /**
         * Returns a TimeSpan that represents a specified number of hours.
         */
        static TimeSpan FromHours(const System::Double& value);

        /**
         * Returns a TimeSpan that represents a specified number of milliseconds.
         */
        static TimeSpan FromMilliseconds(const System::Double& value);

        /**
         * Returns a TimeSpan that represents a specified number of minutes.
         */
        static TimeSpan FromMinutes(const System::Double& value);

        /**
         * Returns a TimeSpan that represents a specified number of seconds.
         */
        static TimeSpan FromSeconds(const System::Double& value);

        /**
         * Returns a TimeSpan that represents a specified time.
         */
        static TimeSpan FromTicks(const int64_t& value);

    public:
        /**
         * Initializes a new instance of the TimeSpan class with the given ticks value.
         */
        TimeSpan(const int64_t& ticks);

        /**
         * Initializes a new instance of the TimeSpan class with the given hours, minutes and seconds.
         */
        TimeSpan(const int32_t& hours
               , const int32_t& minutes
               , const int32_t& seconds);

        /**
         * Initializes a new instance of the TimeSpan class with the given days, hours, minutes and seconds.
         */
        TimeSpan(const int32_t& days
               , const int32_t& hours
               , const int32_t& minutes
               , const int32_t& seconds);

        /**
         * Initializes a new instance of the TimeSpan class with the given days, hours, minutes, seconds and milliseconds.
         */
        TimeSpan(const int32_t& days
               , const int32_t& hours
               , const int32_t& minutes
               , const int32_t& seconds
               , const int32_t& milliseconds);

        /**
         * Initializes a new instance of the TimeSpan class with the given timespan.
         */
        TimeSpan(const TimeSpan& interval);

        /**
         * Releases all resources being used by this TimeSpan.
         */
        ~TimeSpan();

    public:
        /**
         * Returns a new TimeSpan object whose value is the absolute value of this instance.
         */
        TimeSpan Duration() const;

        /**
         * Returns a new TimeSpan object whose value is the negated value of this instance.
         */
        TimeSpan Negate() const;

        /**
         * Gets the days component of the time interval represented by the current TimeSpan structure.
         */
        int32_t Days() const;

        /**
         * Gets the hours component of the time interval represented by the current TimeSpan structure.
         */
        int32_t Hours() const;

        /**
         * Gets the milliseconds component of the time interval represented by the current TimeSpan structure.
         */
        int32_t Milliseconds() const;

        /**
         * Gets the minutes component of the time interval represented by the current TimeSpan structure.
         */
        int32_t Minutes() const;

        /**
         * Gets the seconds component of the time interval represented by the current TimeSpan structure.
         */
        int32_t Seconds() const;

        /**
         * Gets the number of ticks that represent the value of the current TimeSpan structure.
         */
        int64_t Ticks() const;

        /**
         * Gets the value of the current TimeSpan structure expressed in whole and fractional days.
         */
        System::Double TotalDays() const;

        /**
         * Gets the value of the current TimeSpan structure expressed in whole and fractional hours.
         */
        System::Double TotalHours() const;

        /**
         * Gets the value of the current TimeSpan structure expressed in whole and fractional milliseconds.
         */
        System::Double TotalMilliseconds() const;

        /**
         * Gets the value of the current TimeSpan structure expressed in whole and fractional minutes.
         */
        System::Double TotalMinutes() const;

        /**
         * Gets the value of the current TimeSpan structure expressed in whole and fractional seconds.
         */
        System::Double TotalSeconds() const;

        /**
         * Returns a TimeSpan that represents a specified duration type.
         */
        template <class _Duration>
        TimeSpan::Clock::duration ToDuration() const
        {
            return std::chrono::duration_cast<_Duration>(this->ticks);
        }

    public:
        TimeSpan& operator=(const TimeSpan& t2);
        bool operator==(const TimeSpan& t2) const;
        bool operator!=(const TimeSpan& t2) const;
        bool operator>(const TimeSpan& t2) const;
        bool operator>=(const TimeSpan& t2) const;
        bool operator<(const TimeSpan& t2) const;
        bool operator<=(const TimeSpan& t2) const;
        TimeSpan& operator-=(const TimeSpan& t2);
        TimeSpan& operator+=(const TimeSpan& t2);
        const TimeSpan operator-(const TimeSpan& t2) const;
        const TimeSpan operator+(const TimeSpan& t2) const;

    private:
        TimeSpan::TicksDuration ticks;
    };
}

#endif /* TIMESPAN_HPP */
