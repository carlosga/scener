// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/TimeSpan.hpp"

#include <cstdlib>

namespace SceneR {

const TimeSpan     TimeSpan::max_value { INT64_MAX };
const TimeSpan     TimeSpan::min_value { INT64_MIN };
const std::int64_t TimeSpan::ticks_per_day;
const std::int64_t TimeSpan::ticks_per_hour;
const std::int64_t TimeSpan::ticks_per_millisecond;
const std::int64_t TimeSpan::ticks_per_minute;
const std::int64_t TimeSpan::ticks_per_second;
const TimeSpan     TimeSpan::zero      { 0 };

TimeSpan TimeSpan::from_days(const double& value) noexcept
{
    return { std::chrono::duration_cast<ticks_duration>(days_duration(value)).count() };
}

TimeSpan TimeSpan::from_duration(const TimeSpan::clock::duration& value) noexcept
{
    return { std::chrono::duration_cast<ticks_duration>(value).count() };
}

TimeSpan TimeSpan::from_hours(const double& value) noexcept
{
    return { std::chrono::duration_cast<ticks_duration>(hours_duration(value)).count() };
}

TimeSpan TimeSpan::from_milliseconds(const double& value) noexcept
{
    return { std::chrono::duration_cast<ticks_duration>(milli_seconds_duration(value)).count() };
}

TimeSpan TimeSpan::from_minutes(const double& value) noexcept
{
    return { std::chrono::duration_cast<ticks_duration>(minutes_duration(value)).count() };
}

TimeSpan TimeSpan::from_seconds(const double& value) noexcept
{
    return { std::chrono::duration_cast<ticks_duration>(seconds_duration(value)).count() };
}

TimeSpan TimeSpan::from_ticks(const std::int64_t& value) noexcept
{
    return { value };
}

TimeSpan::TimeSpan(const std::int64_t& ticks) noexcept
    : _ticks { ticks_duration(ticks) }
{
}

TimeSpan::TimeSpan(const std::int32_t& hours, const std::int32_t& minutes, const std::int32_t& seconds) noexcept
    : TimeSpan { 0, hours, minutes, seconds, 0 }
{
}

TimeSpan::TimeSpan(const std::int32_t& days
                 , const std::int32_t& hours
                 , const std::int32_t& minutes
                 , const std::int32_t& seconds) noexcept
    : TimeSpan { days, hours, minutes, seconds, 0 }
{
}

TimeSpan::TimeSpan(const std::int32_t& days
                 , const std::int32_t& hours
                 , const std::int32_t& minutes
                 , const std::int32_t& seconds
                 , const std::int32_t& milliseconds) noexcept
{
    _ticks = (std::chrono::duration_cast<ticks_duration>(days_duration(days))
            + std::chrono::duration_cast<ticks_duration>(hours_duration(hours))
            + std::chrono::duration_cast<ticks_duration>(minutes_duration(minutes))
            + std::chrono::duration_cast<ticks_duration>(seconds_duration(seconds))
            + std::chrono::duration_cast<ticks_duration>(milli_seconds_duration(milliseconds)));
}

TimeSpan TimeSpan::duration() const noexcept
{
    return { std::abs(_ticks.count()) };
}

TimeSpan TimeSpan::negate() const noexcept
{
    return { -_ticks.count() };
}

std::int32_t TimeSpan::days() const noexcept
{
    return (_ticks.count() / TimeSpan::ticks_per_day);
}

std::int32_t TimeSpan::hours() const noexcept
{
    return (_ticks.count() % TimeSpan::ticks_per_day / TimeSpan::ticks_per_hour);
}

std::int32_t TimeSpan::milli_seconds() const noexcept
{
    return (_ticks.count() % TimeSpan::ticks_per_second / TimeSpan::ticks_per_millisecond);
}

std::int32_t TimeSpan::minutes() const noexcept
{
    return (_ticks.count() % TimeSpan::ticks_per_hour / TimeSpan::ticks_per_minute);
}

std::int32_t TimeSpan::seconds() const noexcept
{
    return (_ticks.count() % TimeSpan::ticks_per_minute / TimeSpan::ticks_per_second);
}

std::int64_t TimeSpan::ticks() const noexcept
{
    return _ticks.count();
}

double TimeSpan::total_days() const noexcept
{
    return std::chrono::duration_cast<days_duration>(_ticks).count();
}

double TimeSpan::total_hours() const noexcept
{
    return std::chrono::duration_cast<hours_duration>(_ticks).count();
}

double TimeSpan::total_milli_seconds() const noexcept
{
    return std::chrono::duration_cast<milli_seconds_duration>(_ticks).count();
}

double TimeSpan::total_minutes() const noexcept
{
    return std::chrono::duration_cast<minutes_duration>(_ticks).count();
}

double TimeSpan::total_seconds() const noexcept
{
    return std::chrono::duration_cast<seconds_duration>(_ticks).count();
}

bool TimeSpan::operator==(const TimeSpan& t2) const
{
    return (_ticks == t2._ticks);
}

bool TimeSpan::operator!=(const TimeSpan& t2) const
{
    return !(*this == t2);
}

bool TimeSpan::operator>(const TimeSpan& t2) const
{
    return (_ticks > t2._ticks);
}

bool TimeSpan::operator>=(const TimeSpan& t2) const
{
    return (_ticks >= t2._ticks);
}

bool TimeSpan::operator<(const TimeSpan& t2) const
{
    return (_ticks < t2._ticks);
}

bool TimeSpan::operator<=(const TimeSpan& t2) const
{
    return (_ticks <= t2._ticks);
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& t2)
{
    _ticks -= t2._ticks;

    return *this;
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& t2)
{
    _ticks += t2._ticks;

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

}
