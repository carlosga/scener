// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_KEYFRAME_HPP
#define SCENER_GRAPHICS_KEYFRAME_HPP

#include "SceneR/TimeSpan.hpp"
#include "SceneR/Math/Matrix.hpp"

namespace SceneR { namespace Graphics {

/// Defines a position keyframe for an animation.
class Keyframe final
{
public:
    /// Initializes a new instance of the Keyframe class.
    Keyframe() noexcept;

    /// Initializes a new instance of the Keyframe class.
    /// \param time specifies the time, in seconds, at which this keyframe occurs.
    /// \param transform the keyframe transformation.
    Keyframe(const SceneR::TimeSpan& time, const SceneR::Math::Matrix& transform) noexcept;

public:
    /// Gets the time, in seconds, at which this keyframe occurs.
    /// \returns the time, in seconds, at which this keyframe occurs.
    const SceneR::TimeSpan& time() const noexcept;

    /// Gets the keyframe transformation.
    /// \returns the keyframe transformation.
    const SceneR::Math::Matrix& transform() const noexcept;

private:
    SceneR::TimeSpan     _time;
    SceneR::Math::Matrix _transform;
};

}}

#endif // SCENER_GRAPHICS_KEYFRAME_HPP
