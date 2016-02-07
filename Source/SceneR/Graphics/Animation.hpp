// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_ANIMATION_HPP
#define SCENER_GRAPHICS_ANIMATION_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "SceneR/Graphics/Keyframe.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

/// Stores keyframe based animations.
class Animation final
{
public:
    /// Initializes a new instance of the Animatin class.
    Animation() = default;

public:
    /// Gets the current time of the animation.
    /// \returns the current time of the animation.
    const SceneR::TimeSpan& current_time() const noexcept;

    /// Gets the animation duration.
    /// \returns the animation duration.
    const SceneR::TimeSpan& duration() const noexcept;

    /// Gets the list of animation keyframes.
    /// \returns the list of animation keyframes.
    const std::vector<Keyframe>& keyframes() const noexcept;

    /// Gets the current keyframe of the animation.
    const Keyframe& current_keyframe() const noexcept;

    /// Gets the animation name.
    /// \returns the animation name.
    const std::string& name() const noexcept;

    /// Updates the animation state for the given time.
    /// \param time snapshot of the rendering timing state.
    /// \param relativeToCurrentTime indicates if the update should take place against the animation current time.
    void update(const SceneR::TimeSpan& time, bool relativeToCurrentTime) noexcept;

private:
    SceneR::TimeSpan      _current_time     { 0 };
    SceneR::TimeSpan      _duration         { 0 };
    std::size_t           _current_keyframe { 0 };
    std::vector<Keyframe> _keyframes        { };
    std::string           _name             { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_ANIMATION_HPP
