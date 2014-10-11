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

#include <PlaneTest.hpp>

#include <Framework/Plane.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(PlaneTest, TransformPlaneByQuaternion)
{
    Plane      pin(1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion q    = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, MathHelper::PiOver2);
    Plane      pout = Plane::Transform(pin, q);

    EXPECT_TRUE(0.0f        == pout.Normal().X());
    EXPECT_TRUE(0.99999994f == pout.Normal().Y());
    EXPECT_TRUE(0.0f        == pout.Normal().Z());
    EXPECT_TRUE(0.0f        == pout.D());
}

