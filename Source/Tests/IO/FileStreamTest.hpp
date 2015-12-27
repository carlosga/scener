// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TESTS_FILESTREAMTEST_HPP
#define	TESTS_FILESTREAMTEST_HPP

#include <gtest/gtest.h>

class FileStreamTest : public testing::Test
{
protected:
    const std::string TEST_FILE = "/home/carlos/development/projects/cpp/opengl/scener/SceneR.Framework/Resources/BasicEffect.vert";

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp()
    {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }
};

#endif // TESTS_FILESTREAMTEST_HPP
