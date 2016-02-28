// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TESTS_UTF8ENCODINGTESTS_HPP
#define	TESTS_UTF8ENCODINGTESTS_HPP

#include <gtest/gtest.h>

class utf8_encoding_test : public testing::Test
{
protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    void SetUp() override
    {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }
};

#endif // TESTS_UTF8ENCODINGTESTS_HPP
