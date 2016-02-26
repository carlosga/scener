// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_KEYFRAME_HPP
#define SCENER_GRAPHICS_KEYFRAME_HPP

#include "scener/timespan.hpp"
#include "scener/math/matrix.hpp"

namespace scener { namespace graphics {

/// Defines a position keyframe for an animation.
class Keyframe final
{
public:
    /// Initializes a new instance of the Keyframe class.
    Keyframe() noexcept;

    /// Initializes a new instance of the Keyframe class.
    /// \param time specifies the time, in seconds, at which this keyframe occurs.
    /// \param transform the keyframe transformation.
    Keyframe(const scener::timespan& time, const scener::math::matrix4& transform) noexcept;

public:
    /// Gets the time, in seconds, at which this keyframe occurs.
    /// \returns the time, in seconds, at which this keyframe occurs.
    const scener::timespan& time() const noexcept;

    /// Gets the keyframe transformation.
    /// \returns the keyframe transformation.
    const scener::math::matrix4& transform() const noexcept;

private:
    scener::timespan      _time;
    scener::math::matrix4 _transform;
};

}}

#endif // SCENER_GRAPHICS_KEYFRAME_HPP
