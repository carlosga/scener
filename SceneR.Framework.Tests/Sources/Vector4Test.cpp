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
