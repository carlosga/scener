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

#include <Framework/Vector2.hpp>
#include <Vector2Test.hpp>

using namespace SceneR::Framework;

TEST_F(Vector2Test, IndividualCoordinatesConstructor)
{
    float x = 20.0f;
    float y = 30.0f;

    Vector2 vector3(x, y);

    // vector2 is equal to (20.0, 30.0)
    EXPECT_TRUE(x == vector3.X());
    EXPECT_TRUE(y == vector3.Y());
}

TEST_F(Vector2Test, Lerp)
{
    Vector2 value1(5.0f, 10.0f);
    Vector2 value2(0.0f, -20.0f);
    Vector2 vector = Vector2::Lerp(value1, value2, 0.4f);

    EXPECT_TRUE(3.0f == vector.X());
    EXPECT_TRUE(-2.0f == vector.Y());
}
