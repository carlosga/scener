// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/gltf/node.hpp"

namespace scener { namespace content { namespace gltf {

using scener::math::matrix4;
using scener::math::quaternion;
using scener::math::vector3;

node::node() noexcept
    : name          ()
    , camera        ()
    , instance_skin { nullptr }
    , joint         { nullptr }
    , light         ()
    , matrix        { matrix4::identity() }
    , meshes        ()
    , rotation      { quaternion::identity() }
    , scale         { vector3::one() }
    , translation   { vector3::zero() }
    , children      ()
{
}

}}}
