// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_ANIMATION_HPP
#define SCENER_GRAPHICS_ANIMATION_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "scener/graphics/Keyframe.hpp"

namespace scener { namespace content { namespace readers { template <typename T> class content_type_reader; } } }

namespace scener { namespace graphics {

/// Stores keyframe based animations.
class animation final
{
public:
    /// Initializes a new instance of the Animatin class.
    animation() = default;

public:
    /// Gets the current time of the animation.
    /// \returns the current time of the animation.
    const scener::timespan& current_time() const noexcept;

    /// Gets the animation duration.
    /// \returns the animation duration.
    const scener::timespan& duration() const noexcept;

    /// Gets the list of animation keyframes.
    /// \returns the list of animation keyframes.
    const std::vector<keyframe>& keyframes() const noexcept;

    /// Gets the current keyframe of the animation.
    const keyframe& current_keyframe() const noexcept;

    /// Gets the animation name.
    /// \returns the animation name.
    const std::string& name() const noexcept;

    /// Updates the animation state for the given time.
    /// \param time snapshot of the rendering timing state.
    /// \param relativeToCurrentTime indicates if the update should take place against the animation current time.
    void update(const scener::timespan& time, bool relativeToCurrentTime) noexcept;

private:
    scener::timespan      _current_time     { 0 };
    scener::timespan      _duration         { 0 };
    std::size_t           _current_keyframe { 0 };
    std::vector<keyframe> _keyframes        { };
    std::string           _name             { };

    template <typename T> friend class scener::content::readers::content_type_reader;
};

}}

#endif // SCENER_GRAPHICS_ANIMATION_HPP
