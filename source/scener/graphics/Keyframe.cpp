// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/Keyframe.hpp"

namespace scener { namespace graphics {

using scener::time_span;
using scener::math::matrix4;

Keyframe::Keyframe() noexcept
    : Keyframe { time_span::zero(), matrix4::identity() }
{
}

Keyframe::Keyframe(const time_span& time, const matrix4& transform) noexcept
    : _time      { time }
    , _transform { transform }
{
}

const time_span& Keyframe::time() const noexcept
{
    return _time;
}

const matrix4& Keyframe::transform() const noexcept
{
    return _transform;
}

}}
