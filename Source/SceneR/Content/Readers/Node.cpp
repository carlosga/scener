// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/Node.hpp>

#include <Math/Matrix.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector3.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Math::Matrix;
        using SceneR::Math::Quaternion;
        using SceneR::Math::Vector3;

        Node::Node() noexcept
            : name          ()
            , camera        ()
            , instance_skin { nullptr }
            , joint         { nullptr }
            , light         ()
            , matrix        { Matrix::identity }
            , meshes        ()
            , rotation      { Quaternion::identity }
            , scale         { Vector3::one }
            , translation   { Vector3::zero }
            , children      ()
        {
        }
    }
}
