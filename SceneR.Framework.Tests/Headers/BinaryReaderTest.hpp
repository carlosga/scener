// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BINARYREADERTEST_HPP
#define	BINARYREADERTEST_HPP

#include <gtest/gtest.h>

#include <System/Core.hpp>

class BinaryReaderTest : public ::testing::Test
{
protected:
    const System::String TEST_FILE = u"/home/carlos/development/projects/cpp/opengl/scener/SceneR.Framework/Resources/BasicEffect.vert";

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp()
    {
    };

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }
};

#endif	// BINARYREADERTEST_HPP
