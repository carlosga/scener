// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Node.hpp>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector3;

        Node::Node()
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

        Node::~Node()
        {
        }
    }
}
