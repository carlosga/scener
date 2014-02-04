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

#include <System/TimeSpan.hpp>
#include <TimeSpanTest.hpp>

using namespace System;

TEST_F(TimeSpanTest, Max)
{
    auto interval = TimeSpan::MaxValue;

    EXPECT_TRUE(interval.Ticks()        == 9223372036854775807);
    EXPECT_TRUE(interval.Days()         == 10675199);
    EXPECT_TRUE(interval.Hours()        == 02);
    EXPECT_TRUE(interval.Minutes()      == 48);
    EXPECT_TRUE(interval.Seconds()      == 05);
    EXPECT_TRUE(interval.Milliseconds() == 477);
}

TEST_F(TimeSpanTest, Min)
{
    auto interval = TimeSpan::MinValue;

    EXPECT_TRUE(interval.Ticks()        == INT64_MIN);
    EXPECT_TRUE(interval.Days()         == -10675199);
    EXPECT_TRUE(interval.Hours()        == -02);
    EXPECT_TRUE(interval.Minutes()      == -48);
    EXPECT_TRUE(interval.Seconds()      == -05);
    EXPECT_TRUE(interval.Milliseconds() == -477);
}

TEST_F(TimeSpanTest, FromDays)
{
    auto interval = TimeSpan::FromDays(12345.678987654);

    EXPECT_TRUE(interval.Days()         == 12345);
    EXPECT_TRUE(interval.Hours()        == 16);
    EXPECT_TRUE(interval.Minutes()      == 17);
    EXPECT_TRUE(interval.Seconds()      == 44);
    EXPECT_TRUE(interval.Milliseconds() == 533);
}

TEST_F(TimeSpanTest, FromHours)
{
    auto interval = TimeSpan::FromHours(123456.7898765);

    EXPECT_TRUE(interval.Days()         == 5144);
    EXPECT_TRUE(interval.Hours()        == 0);
    EXPECT_TRUE(interval.Minutes()      == 47);
    EXPECT_TRUE(interval.Seconds()      == 23);
    EXPECT_TRUE(interval.Milliseconds() == 555);
}

TEST_F(TimeSpanTest, FromMilliseconds)
{
    auto interval = TimeSpan::FromMilliseconds(1234567898765.4);

    EXPECT_TRUE(interval.Days()         == 14288);
    EXPECT_TRUE(interval.Hours()        == 23);
    EXPECT_TRUE(interval.Minutes()      == 31);
    EXPECT_TRUE(interval.Seconds()      == 38);
    EXPECT_TRUE(interval.Milliseconds() == 765);
}

TEST_F(TimeSpanTest, FromMinutes)
{
    auto interval = TimeSpan::FromMinutes(12345678.98765);

    EXPECT_TRUE(interval.Days()         == 8573);
    EXPECT_TRUE(interval.Hours()        == 9);
    EXPECT_TRUE(interval.Minutes()      == 18);
    EXPECT_TRUE(interval.Seconds()      == 59);
    EXPECT_TRUE(interval.Milliseconds() == 259);
}

TEST_F(TimeSpanTest, FromSeconds)
{
    auto interval = TimeSpan::FromSeconds(1234567898.7654);

    EXPECT_TRUE(interval.Days()         == 14288);
    EXPECT_TRUE(interval.Hours()        == 23);
    EXPECT_TRUE(interval.Minutes()      == 31);
    EXPECT_TRUE(interval.Seconds()      == 38);
    EXPECT_TRUE(interval.Milliseconds() == 765);
}

TEST_F(TimeSpanTest, FromTicks)
{
    auto interval = TimeSpan::FromTicks(12345678987654321);

    EXPECT_TRUE(interval.Days()         == 14288);
    EXPECT_TRUE(interval.Hours()        == 23);
    EXPECT_TRUE(interval.Minutes()      == 31);
    EXPECT_TRUE(interval.Seconds()      == 38);
    EXPECT_TRUE(interval.Milliseconds() == 765);
}

TEST_F(TimeSpanTest, Zero)
{
    auto interval = TimeSpan::Zero;

    EXPECT_TRUE(interval.Ticks()        == 0);
    EXPECT_TRUE(interval.Days()         == 0);
    EXPECT_TRUE(interval.Hours()        == 0);
    EXPECT_TRUE(interval.Minutes()      == 0);
    EXPECT_TRUE(interval.Seconds()      == 0);
    EXPECT_TRUE(interval.Milliseconds() == 0);
}

TEST_F(TimeSpanTest, Days)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.Days() == 10);
}

TEST_F(TimeSpanTest, Hours)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.Hours() == 20);
}

TEST_F(TimeSpanTest, Minutes)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.Minutes() == 30);
}

TEST_F(TimeSpanTest, Seconds)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.Seconds() == 40);
}

TEST_F(TimeSpanTest, Milliseconds)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.Milliseconds() == 50);
}

TEST_F(TimeSpanTest, Ticks)
{
    auto interval = TimeSpan { 10, 20, 30, 40, 50 };

    EXPECT_TRUE(interval.Ticks() == 9378400500000);
}

TEST_F(TimeSpanTest, TotalDays)
{
    auto interval = TimeSpan { 3, 16, 42, 45, 750 };

    EXPECT_TRUE(interval.TotalDays() == 3.6963628472222223);
}

TEST_F(TimeSpanTest, TotalHours)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.TotalHours() == 39.712708333333332);
}

TEST_F(TimeSpanTest, TotalMilliseconds)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.TotalMilliseconds() == 142965750);
}

TEST_F(TimeSpanTest, TotalMinutes)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.TotalMinutes() == 2382.7624999999998);
}

TEST_F(TimeSpanTest, TotalSeconds)
{
    auto interval = TimeSpan { 1, 15, 42, 45, 750 };

    EXPECT_TRUE(interval.TotalSeconds() == 142965.75);
}
