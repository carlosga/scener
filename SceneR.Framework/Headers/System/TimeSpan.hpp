//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <System/Core.hpp>
#include <chrono>
#include <ratio>

namespace System
{
    /**
     * Represents a time interval.
     */
    struct TimeSpan
    {
    public:
        typedef std::chrono::high_resolution_clock                             Clock;
        typedef std::chrono::duration<System::Double, std::ratio<86400>>       DaysDuration;
        typedef std::chrono::duration<System::Double, std::ratio<3600>>        HoursDuration;
        typedef std::chrono::duration<System::Double, std::ratio<60>>          MinutesDuration;
        typedef std::chrono::duration<System::Double>                          SecondsDuration;
        typedef std::chrono::duration<System::Double, std::ratio<1, 1000>>     MillisecondsDuration;
        typedef std::chrono::duration<System::Double, std::ratio<1, 1000000>>  MicrosecondsDuration;
        typedef std::chrono::duration<System::Int64 , std::ratio<1, 10000000>> TicksDuration;

    public:
        /**
         * Represents the maximum TimeSpan value.
         */
        static const TimeSpan& MaxValue;

        /**
         * Represents the minimum TimeSpan value.
         */
        static const TimeSpan& MinValue;

        /**
         * Represents the number of ticks in 1 day.
         */
        static const System::Int64& TicksPerDay;

        /**
         * Represents the number of ticks in 1 hour.
         */
        static const System::Int64& TicksPerHour;

        /**
         * Represents the number of ticks in 1 millisecond.
         */
        static const System::Int64& TicksPerMillisecond;

        /**
         * Represents the number of ticks in 1 minute.
         */
        static const System::Int64& TicksPerMinute;

        /**
         * Represents the number of ticks in 1 second.
         */
        static const System::Int64& TicksPerSecond;

        /**
         * Represents the zero TimeSpan value. This field is read-only.
         */
        static const TimeSpan& Zero;

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
        static TimeSpan FromTicks(const System::Int64& value);

    public:
        /**
         * Initializes a new instance of the TimeSpan class with the given ticks value.
         */
        TimeSpan(const System::Int64& ticks);

        /**
         * Initializes a new instance of the TimeSpan class with the given hours, minutes and seconds.
         */
        TimeSpan(const System::Int32& hours
               , const System::Int32& minutes
               , const System::Int32& seconds);

        /**
         * Initializes a new instance of the TimeSpan class with the given days, hours, minutes and seconds.
         */
        TimeSpan(const System::Int32& days
               , const System::Int32& hours
               , const System::Int32& minutes
               , const System::Int32& seconds);

        /**
         * Initializes a new instance of the TimeSpan class with the given days, hours, minutes, seconds and milliseconds.
         */
        TimeSpan(const System::Int32& days
               , const System::Int32& hours
               , const System::Int32& minutes
               , const System::Int32& seconds
               , const System::Int32& milliseconds);

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
        System::Int32 Days() const;

        /**
         * Gets the hours component of the time interval represented by the current TimeSpan structure.
         */
        System::Int32 Hours() const;

        /**
         * Gets the milliseconds component of the time interval represented by the current TimeSpan structure.
         */
        System::Int32 Milliseconds() const;

        /**
         * Gets the minutes component of the time interval represented by the current TimeSpan structure.
         */
        System::Int32 Minutes() const;

        /**
         * Gets the seconds component of the time interval represented by the current TimeSpan structure.
         */
        System::Int32 Seconds() const;

        /**
         * Gets the number of ticks that represent the value of the current TimeSpan structure.
         */
        System::Int64 Ticks() const;

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
        };

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
