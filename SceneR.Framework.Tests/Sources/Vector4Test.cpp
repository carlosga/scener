// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Vector4Test.hpp>

#include <Framework/Matrix.hpp>
#include <Framework/Vector4.hpp>

using namespace SceneR::Framework;

TEST_F(Vector4Test, VectorMatrixMultiplication)
{
    auto point  = Vector4 { 10.0f, 5.0f, 1.0f, 4.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };
    auto result = point * matrix;

    // pointResult is equal to (250, 270, 290, 4)
    EXPECT_TRUE(result.X() == 250.0f);
    EXPECT_TRUE(result.Y() == 270.0f);
    EXPECT_TRUE(result.Z() == 290.0f);
    EXPECT_TRUE(result.W() == 4.0f);
}
