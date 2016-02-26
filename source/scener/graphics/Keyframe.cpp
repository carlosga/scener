// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Keyframe.hpp"

namespace scener { namespace graphics {

using scener::TimeSpan;
using scener::math::matrix4;

Keyframe::Keyframe() noexcept
    : Keyframe { TimeSpan::zero(), matrix4::identity() }
{
}

Keyframe::Keyframe(const TimeSpan& time, const matrix4& transform) noexcept
    : _time      { time }
    , _transform { transform }
{
}

const TimeSpan& Keyframe::time() const noexcept
{
    return _time;
}

const matrix4& Keyframe::transform() const noexcept
{
    return _transform;
}

}}
