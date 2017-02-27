// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "timespan_test.hpp"

#include <scener/timespan.hpp>

using namespace scener;

TEST_F(timespan_test, max)
{
    auto interval = timespan::max_value();

    EXPECT_TRUE(interval.ticks()         == 9223372036854775807);
    EXPECT_TRUE(interval.days()          == 10675199);
    EXPECT_TRUE(interval.hours()         == 02);
    EXPECT_TRUE(interval.minutes()       == 48);
    EXPECT_TRUE(interval.seconds()       == 05);
    EXPECT_TRUE(interval.milli_seconds() == 477);
}

TEST_F(timespan_test, min)
{
    auto interval = timespan::min_value();

    EXPECT_TRUE(interval.ticks()         == INT64_MIN);
    EXPECT_TRUE(interval.days()          == -10675199);
    EXPECT_TRUE(interval.hours()         == -02);
    EXPECT_TRUE(interval.minutes()       == -48);
    EXPECT_TRUE(interval.seconds()       == -05);
    EXPECT_TRUE(interval.milli_seconds() == -477);
}

TEST_F(timespan_test, from_days)
{
    auto interval = timespan::from_days(12345.678987654);

    EXPECT_TRUE(interval.days()          == 12345);
    EXPECT_TRUE(interval.hours()         == 16);
    EXPECT_TRUE(interval.minutes()       == 17);
    EXPECT_TRUE(interval.seconds()       == 44);
    EXPECT_TRUE(interval.milli_seconds() == 533);
}

TEST_F(timespan_test, from_hours)
{
    auto interval = timespan::from_hours(123456.7898765);

    EXPECT_TRUE(interval.days()          == 5144);
    EXPECT_TRUE(interval.hours()         == 0);
    EXPECT_TRUE(interval.minutes()       == 47);
    EXPECT_TRUE(interval.seconds()       == 23);
    EXPECT_TRUE(interval.milli_seconds() == 555);
}

TEST_F(timespan_test, from_milliseconds)
{
    auto interval = timespan::from_milliseconds(1234567898765.4);

    EXPECT_TRUE(interval.days()          == 14288);
    EXPECT_TRUE(interval.hours()         == 23);
    EXPECT_TRUE(interval.minutes()       == 31);
    EXPECT_TRUE(interval.seconds()       == 38);
    EXPECT_TRUE(interval.milli_seconds() == 765);
}

TEST_F(timespan_test, from_minutes)
{
    auto interval = timespan::from_minutes(12345678.98765);

    EXPECT_TRUE(interval.days()          == 8573);
    EXPECT_TRUE(interval.hours()         == 9);
    EXPECT_TRUE(interval.minutes()       == 18);
    EXPECT_TRUE(interval.seconds()       == 59);
    EXPECT_TRUE(interval.milli_seconds() == 259);
}

TEST_F(timespan_test, from_seconds)
{
    auto interval = timespan::from_seconds(1234567898.7654);

    EXPECT_TRUE(interval.days()          == 14288);
    EXPECT_TRUE(interval.hours()         == 23);
    EXPECT_TRUE(interval.minutes()       == 31);
    EXPECT_TRUE(interval.seconds()       == 38);
    EXPECT_TRUE(interval.milli_seconds() == 765);
}

TEST_F(timespan_test, from_ticks)
{
    auto interval = timespan::from_ticks(12345678987654321);

    EXPECT_TRUE(interval.days()          == 14288);
    EXPECT_TRUE(interval.hours()         == 23);
    EXPECT_TRUE(interval.minutes()       == 31);
    EXPECT_TRUE(interval.seconds()       == 38);
    EXPECT_TRUE(interval.milli_seconds() == 765);
}

TEST_F(timespan_test, zero)
{
    auto interval = timespan::zero();

    EXPECT_TRUE(interval.ticks()         == 0);
    EXPECT_TRUE(interval.days()          == 0);
    EXPECT_TRUE(interval.hours()         == 0);
    EXPECT_TRUE(interval.minutes()       == 0);
    EXPECT_TRUE(interval.seconds()       == 0);
    EXPECT_TRUE(interval.milli_seconds() == 0);
}

TEST_F(timespan_test, days)
{
    auto interval = timespan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.days() == 10);
}

TEST_F(timespan_test, hours)
{
    auto interval = timespan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.hours() == 20);
}

TEST_F(timespan_test, minutes)
{
    auto interval = timespan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.minutes() == 30);
}

TEST_F(timespan_test, seconds)
{
    auto interval = timespan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.seconds() == 40);
}

TEST_F(timespan_test, milliseconds)
{
    auto interval = timespan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.milli_seconds() == 50);
}

TEST_F(timespan_test, ticks)
{
    auto interval = timespan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.ticks() == 9378400500000);
}

TEST_F(timespan_test, total_days)
{
    auto interval = timespan { 3, 16, 42, 45, 750 };

    EXPECT_TRUE(interval.total_days() == 3.6963628472222223);
}

TEST_F(timespan_test, total_hours)
{
    auto interval = timespan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_hours() == 39.712708333333332);
}

TEST_F(timespan_test, total_milliseconds)
{
    auto interval = timespan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_milli_seconds() == 142965750);
}

TEST_F(timespan_test, total_minutes)
{
    auto interval = timespan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_minutes() == 2382.7624999999998);
}

TEST_F(timespan_test, total_seconds)
{
    auto interval = timespan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_seconds() == 142965.75);
}
