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

#include <MathHelperTest.hpp>

#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(MathHelperTest, Clamp)
{
    Single value = MathHelper::Clamp(10.0f, 0.0f, 3.0f);

    EXPECT_TRUE(3.0f == value);
}

TEST_F(MathHelperTest, Lerp)
{
    Single value1 = MathHelper::Lerp(50.0f, 100.0f, 0.5f);

    EXPECT_TRUE(75.0f == value1);

    Single value2 = MathHelper::Lerp(50.0f, 100.0f, 0.3f);

    EXPECT_TRUE(65.0f == value2);

    Single value3 = MathHelper::Lerp(10.0f, 20.0f, 0.0f);

    EXPECT_TRUE(10.0f == value3);

    Single value4 = MathHelper::Lerp(10.0f, 20.0f, 0.2f);

    EXPECT_TRUE(12.0f == value4);

    Single value5 = MathHelper::Lerp(10.0f, 20.0f, 0.5f);

    EXPECT_TRUE(15.0f == value5);

    Single value6 = MathHelper::Lerp(10.0f, 20.0f, 0.8f);

    EXPECT_TRUE(18.0f == value6);

    Single value7 = MathHelper::Lerp(10.0f, 20.0f, 1.0f);

    EXPECT_TRUE(20.0f == value7);
}
