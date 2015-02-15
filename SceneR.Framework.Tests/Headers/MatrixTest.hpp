// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATRIXTEST_HPP
#define	MATRIXTEST_HPP

#include <gtest/gtest.h>

#include <System/Core.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Plane.hpp>

class MatrixTest : public testing::Test
{
protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp()
    {
    };

    static SceneR::Framework::Matrix GenerateMatrixNumberFrom1To16();
    static SceneR::Framework::Matrix GenerateTestMatrix();
    static void Decompose(const System::Single&             yaw
                        , const System::Single&             pitch
                        , const System::Single&             roll
                        , const SceneR::Framework::Vector3& expectedTranslation
                        , const SceneR::Framework::Vector3& expectedScales);
    static void DecomposeScale(const System::Single& sx, const System::Single& sy, const System::Single& sz);
    static void CreateReflection(const SceneR::Framework::Plane& plane, const SceneR::Framework::Matrix& expected);

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }
};

#endif	// MATRIXTEST_HPP
