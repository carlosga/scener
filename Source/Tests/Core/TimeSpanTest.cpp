// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "TimeSpanTest.hpp"

#include <SceneR/Core/TimeSpan.hpp>

using namespace SceneR;

TEST_F(TimeSpanTest, Max)
{
    auto interval = TimeSpan::max_value;

    EXPECT_TRUE(interval.ticks()        == 9223372036854775807);
    EXPECT_TRUE(interval.days()         == 10675199);
    EXPECT_TRUE(interval.hours()        == 02);
    EXPECT_TRUE(interval.minutes()      == 48);
    EXPECT_TRUE(interval.seconds()      == 05);
    EXPECT_TRUE(interval.milli_seconds() == 477);
}

TEST_F(TimeSpanTest, Min)
{
    auto interval = TimeSpan::min_value;

    EXPECT_TRUE(interval.ticks()        == INT64_MIN);
    EXPECT_TRUE(interval.days()         == -10675199);
    EXPECT_TRUE(interval.hours()        == -02);
    EXPECT_TRUE(interval.minutes()      == -48);
    EXPECT_TRUE(interval.seconds()      == -05);
    EXPECT_TRUE(interval.milli_seconds() == -477);
}

TEST_F(TimeSpanTest, FromDays)
{
    auto interval = TimeSpan::from_days(12345.678987654);

    EXPECT_TRUE(interval.days()         == 12345);
    EXPECT_TRUE(interval.hours()        == 16);
    EXPECT_TRUE(interval.minutes()      == 17);
    EXPECT_TRUE(interval.seconds()      == 44);
    EXPECT_TRUE(interval.milli_seconds() == 533);
}

TEST_F(TimeSpanTest, FromHours)
{
    auto interval = TimeSpan::from_hours(123456.7898765);

    EXPECT_TRUE(interval.days()         == 5144);
    EXPECT_TRUE(interval.hours()        == 0);
    EXPECT_TRUE(interval.minutes()      == 47);
    EXPECT_TRUE(interval.seconds()      == 23);
    EXPECT_TRUE(interval.milli_seconds() == 555);
}

TEST_F(TimeSpanTest, FromMilliseconds)
{
    auto interval = TimeSpan::from_milliseconds(1234567898765.4);

    EXPECT_TRUE(interval.days()         == 14288);
    EXPECT_TRUE(interval.hours()        == 23);
    EXPECT_TRUE(interval.minutes()      == 31);
    EXPECT_TRUE(interval.seconds()      == 38);
    EXPECT_TRUE(interval.milli_seconds() == 765);
}

TEST_F(TimeSpanTest, FromMinutes)
{
    auto interval = TimeSpan::from_minutes(12345678.98765);

    EXPECT_TRUE(interval.days()         == 8573);
    EXPECT_TRUE(interval.hours()        == 9);
    EXPECT_TRUE(interval.minutes()      == 18);
    EXPECT_TRUE(interval.seconds()      == 59);
    EXPECT_TRUE(interval.milli_seconds() == 259);
}

TEST_F(TimeSpanTest, FromSeconds)
{
    auto interval = TimeSpan::from_seconds(1234567898.7654);

    EXPECT_TRUE(interval.days()         == 14288);
    EXPECT_TRUE(interval.hours()        == 23);
    EXPECT_TRUE(interval.minutes()      == 31);
    EXPECT_TRUE(interval.seconds()      == 38);
    EXPECT_TRUE(interval.milli_seconds() == 765);
}

TEST_F(TimeSpanTest, FromTicks)
{
    auto interval = TimeSpan::from_ticks(12345678987654321);

    EXPECT_TRUE(interval.days()         == 14288);
    EXPECT_TRUE(interval.hours()        == 23);
    EXPECT_TRUE(interval.minutes()      == 31);
    EXPECT_TRUE(interval.seconds()      == 38);
    EXPECT_TRUE(interval.milli_seconds() == 765);
}

TEST_F(TimeSpanTest, Zero)
{
    auto interval = TimeSpan::zero;

    EXPECT_TRUE(interval.ticks()        == 0);
    EXPECT_TRUE(interval.days()         == 0);
    EXPECT_TRUE(interval.hours()        == 0);
    EXPECT_TRUE(interval.minutes()      == 0);
    EXPECT_TRUE(interval.seconds()      == 0);
    EXPECT_TRUE(interval.milli_seconds() == 0);
}

TEST_F(TimeSpanTest, Days)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.days() == 10);
}

TEST_F(TimeSpanTest, Hours)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.hours() == 20);
}

TEST_F(TimeSpanTest, Minutes)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.minutes() == 30);
}

TEST_F(TimeSpanTest, Seconds)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.seconds() == 40);
}

TEST_F(TimeSpanTest, Milliseconds)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.milli_seconds() == 50);
}

TEST_F(TimeSpanTest, Ticks)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.ticks() == 9378400500000);
}

TEST_F(TimeSpanTest, TotalDays)
{
    auto interval = TimeSpan { 3, 16, 42, 45, 750 };

    EXPECT_TRUE(interval.total_days() == 3.6963628472222223);
}

TEST_F(TimeSpanTest, TotalHours)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_hours() == 39.712708333333332);
}

TEST_F(TimeSpanTest, TotalMilliseconds)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_milli_seconds() == 142965750);
}

TEST_F(TimeSpanTest, TotalMinutes)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_minutes() == 2382.7624999999998);
}

TEST_F(TimeSpanTest, TotalSeconds)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.total_seconds() == 142965.75);
}
