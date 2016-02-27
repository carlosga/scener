// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/keyframe.hpp"

namespace scener { namespace graphics {

using scener::timespan;
using scener::math::matrix4;

keyframe::keyframe() noexcept
    : keyframe { timespan::zero(), matrix4::identity() }
{
}

keyframe::keyframe(const timespan& time, const matrix4& transform) noexcept
    : _time      { time }
    , _transform { transform }
{
}

const timespan& keyframe::time() const noexcept
{
    return _time;
}

const matrix4& keyframe::transform() const noexcept
{
    return _transform;
}

}}
