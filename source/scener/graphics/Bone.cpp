// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/Bone.hpp"

namespace scener { namespace graphics {

using scener::math::matrix4;

bone::index_type bone::index() const noexcept
{
    return _index;
}

const std::vector<std::shared_ptr<bone>>& bone::children() const noexcept
{
    return _children;
}

const std::string& bone::name() const noexcept
{
    return _name;
}

bone* bone::parent() const noexcept
{
    return _parent.get();
}

animation* bone::animation() const noexcept
{
    return _animation.get();
}

const matrix4& bone::transform() const noexcept
{
    return _transform;
}

void bone::transform(const matrix4& transform) noexcept
{
    _transform = transform;
}

}}
