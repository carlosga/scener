// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
