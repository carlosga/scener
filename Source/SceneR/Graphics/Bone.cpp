// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Bone.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Matrix;

Bone::index_type Bone::index() const noexcept
{
    return _index;
}

const std::vector<std::shared_ptr<Bone>>& Bone::children() const noexcept
{
    return _children;
}

const std::string& Bone::name() const noexcept
{
    return _name;
}

Bone* Bone::parent() const noexcept
{
    return _parent.get();
}

Animation* Bone::animation() const noexcept
{
    return _animation.get();
}

const Matrix& Bone::transform() const noexcept
{
    return _transform;
}

void Bone::transform(const Matrix& transform) noexcept
{
    _transform = transform;
}

}}
