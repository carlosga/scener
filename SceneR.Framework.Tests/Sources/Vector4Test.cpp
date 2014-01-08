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

#include <Framework/Matrix.hpp>
#include <Framework/Vector4.hpp>
#include <Vector4Test.hpp>

using namespace SceneR::Framework;

TEST_F(Vector4Test, VectorMatrixMultiplication)
{
    Vector4 point1(10, 5, 1, 4);
    Matrix  matrix1(10, 10, 10, 0, 20, 20, 20, 0, 30, 30, 30, 0, 5, 10, 15, 1);
    Vector4 pointResult = point1 * matrix1;

    // pointResult is equal to (250, 270, 290, 4)
    EXPECT_TRUE(pointResult.X() == 250.0f);
    EXPECT_TRUE(pointResult.Y() == 270.0f);
    EXPECT_TRUE(pointResult.Z() == 290.0f);
    EXPECT_TRUE(pointResult.W() == 4.0f);
}
