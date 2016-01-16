// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TESTS_MATRIXTEST_HPP
#define	TESTS_MATRIXTEST_HPP

#include <gtest/gtest.h>

#include <SceneR/Math/Matrix.hpp>
#include <SceneR/Math/Plane.hpp>

class MatrixTest : public testing::Test
{
protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    void SetUp() override
    {
    }

    static SceneR::Math::Matrix GenerateMatrixNumberFrom1To16();
    static SceneR::Math::Matrix GenerateTestMatrix();
    static void Decompose(const float&                      yaw
                        , const float&                      pitch
                        , const float&                      roll
                        , const SceneR::Math::Vector3& expectedTranslation
                        , const SceneR::Math::Vector3& expectedScales);
    static void DecomposeScale(const float& sx, const float& sy, const float& sz);
    static void CreateReflection(const SceneR::Math::Plane& plane, const SceneR::Math::Matrix& expected);

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }
};

#endif // TESTS_MATRIXTEST_HPP
