// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/ModelBone.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Matrix;

ModelBone::index_type ModelBone::index() const noexcept
{
    return _index;
}

const std::vector<std::shared_ptr<ModelBone>>& ModelBone::children() const noexcept
{
    return _children;
}

const std::string& ModelBone::name() const noexcept
{
    return _name;
}

ModelBone* ModelBone::parent() const noexcept
{
    return _parent.get();
}

Animation* ModelBone::animation() const noexcept
{
    return _animation.get();
}

const Matrix& ModelBone::transform() const noexcept
{
    return _transform;
}

void ModelBone::transform(const Matrix& transform) noexcept
{
    _transform = transform;
}

}}
