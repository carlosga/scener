// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/TimeSpan.hpp>

#include <cstdlib>

using namespace System;

const TimeSpan& TimeSpan::MaxValue            { INT64_MAX };
const TimeSpan& TimeSpan::MinValue            { INT64_MIN };
const Int64&    TimeSpan::TicksPerDay         = 864000000000;
const Int64&    TimeSpan::TicksPerHour        = 36000000000;
const Int64&    TimeSpan::TicksPerMillisecond = 10000;
const Int64&    TimeSpan::TicksPerMinute      = 600000000;
const Int64&    TimeSpan::TicksPerSecond      = 10000000;
const TimeSpan& TimeSpan::Zero                { 0 };

TimeSpan TimeSpan::FromDays(const System::Double& value)
{
    return { std::chrono::duration_cast<TicksDuration>(DaysDuration(value)).count() };
}

TimeSpan TimeSpan::FromDuration(const TimeSpan::Clock::duration& value)
{
    return { std::chrono::duration_cast<TicksDuration>(value).count() };
}

TimeSpan TimeSpan::FromHours(const Double& value)
{
    return { std::chrono::duration_cast<TicksDuration>(HoursDuration(value)).count() };
}

TimeSpan TimeSpan::FromMilliseconds(const System::Double& value)
{
    return { std::chrono::duration_cast<TicksDuration>(MillisecondsDuration(value)).count() };
}

TimeSpan TimeSpan::FromMinutes(const Double& value)
{
    return { std::chrono::duration_cast<TicksDuration>(MinutesDuration(value)).count() };
}

TimeSpan TimeSpan::FromSeconds(const Double& value)
{
    return { std::chrono::duration_cast<TicksDuration>(SecondsDuration(value)).count() };
}

TimeSpan TimeSpan::FromTicks(const Int64& value)
{
    return { value };
}

TimeSpan::TimeSpan(const Int64& ticks)
    : ticks { TicksDuration(ticks) }
{
}

TimeSpan::TimeSpan(const Int32& hours, const Int32& minutes, const Int32& seconds)
    : TimeSpan { 0, hours, minutes, seconds, 0 }
{
}

TimeSpan::TimeSpan(const Int32& days, const Int32& hours, const Int32& minutes, const Int32& seconds)
    : TimeSpan { days, hours, minutes, seconds, 0 }
{
}

TimeSpan::TimeSpan(const Int32& days
                 , const Int32& hours
                 , const Int32& minutes
                 , const Int32& seconds
                 , const Int32& milliseconds)
{
    this->ticks = (std::chrono::duration_cast<TicksDuration>(DaysDuration(days))
                 + std::chrono::duration_cast<TicksDuration>(HoursDuration(hours))
                 + std::chrono::duration_cast<TicksDuration>(MinutesDuration(minutes))
                 + std::chrono::duration_cast<TicksDuration>(SecondsDuration(seconds))
                 + std::chrono::duration_cast<TicksDuration>(MillisecondsDuration(milliseconds)));
}

TimeSpan::TimeSpan(const TimeSpan& interval)
    : ticks { interval.ticks }
{
}

TimeSpan TimeSpan::Duration() const
{
    return { std::abs(this->ticks.count()) };
}

TimeSpan TimeSpan::Negate() const
{
    return { -this->ticks.count() };
}

Int32 TimeSpan::Days() const
{
    return (this->ticks.count() / TimeSpan::TicksPerDay);
}

Int32 TimeSpan::Hours() const
{
    return (this->ticks.count() % TimeSpan::TicksPerDay / TimeSpan::TicksPerHour);
}

Int32 TimeSpan::Milliseconds() const
{
    return (this->ticks.count() % TimeSpan::TicksPerSecond / TimeSpan::TicksPerMillisecond);
}

Int32 TimeSpan::Minutes() const
{
    return (this->ticks.count() % TimeSpan::TicksPerHour / TimeSpan::TicksPerMinute);
}

Int32 TimeSpan::Seconds() const
{
    return (this->ticks.count() % TimeSpan::TicksPerMinute / TimeSpan::TicksPerSecond);
}

Int64 TimeSpan::Ticks() const
{
    return this->ticks.count();
}

Double TimeSpan::TotalDays() const
{
    return std::chrono::duration_cast<DaysDuration>(this->ticks).count();
}

Double TimeSpan::TotalHours() const
{
    return std::chrono::duration_cast<HoursDuration>(this->ticks).count();
}

Double TimeSpan::TotalMilliseconds() const
{
    return std::chrono::duration_cast<MillisecondsDuration>(this->ticks).count();
}

Double TimeSpan::TotalMinutes() const
{
    return std::chrono::duration_cast<MinutesDuration>(this->ticks).count();
}

Double TimeSpan::TotalSeconds() const
{
    return std::chrono::duration_cast<SecondsDuration>(this->ticks).count();
}

TimeSpan& TimeSpan::operator=(const TimeSpan& t2)
{
    if (this != &t2)
    {
        this->ticks = t2.ticks;
    }

    return *this;
}

bool TimeSpan::operator==(const TimeSpan& t2) const
{
    return (this->ticks == t2.ticks);
}

bool TimeSpan::operator!=(const TimeSpan& t2) const
{
    return !(*this == t2);
}

bool TimeSpan::operator>(const TimeSpan& t2) const
{
    return (this->ticks > t2.ticks);
}

bool TimeSpan::operator>=(const TimeSpan& t2) const
{
    return (this->ticks >= t2.ticks);
}

bool TimeSpan::operator<(const TimeSpan& t2) const
{
    return (this->ticks < t2.ticks);
}

bool TimeSpan::operator<=(const TimeSpan& t2) const
{
    return (this->ticks <= t2.ticks);
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& t2)
{
    this->ticks -= t2.ticks;

    return *this;
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& t2)
{
    this->ticks += t2.ticks;

    return *this;
}

const TimeSpan TimeSpan::operator-(const TimeSpan& t2) const
{
    auto result = *this;

    result -= t2;

    return result;
}

const TimeSpan TimeSpan::operator+(const TimeSpan& t2) const
{
    auto result = *this;

    result += t2;

    return result;
}
