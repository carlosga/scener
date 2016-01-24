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

class Animation final
{
public:
    Animation() = default;
    ~Animation() = default;

public:
    const SceneR::TimeSpan& current_time() const noexcept;
    const SceneR::TimeSpan& duration() const noexcept;
    const std::vector<Keyframe>& keyframes() const noexcept;
    const Keyframe& current_keyframe() const noexcept;
    const std::string& name() const noexcept;
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
