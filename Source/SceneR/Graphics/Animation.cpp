// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Animation.hpp"

#include "SceneR/Math/Math.hpp"

namespace SceneR { namespace Graphics {

using SceneR::TimeSpan;

Animation::Animation()
    : _name()
    , _current_time(0)
    , _current_keyframe(0)
    , _keyframes(0)
{
}

const TimeSpan& Animation::current_time() const noexcept
{
    return _current_time;
}

const TimeSpan& Animation::duration() const noexcept
{
    return _keyframes.crbegin()->time();
}

const std::string& Animation::name() const noexcept
{
    return _name;
}

const std::vector<Keyframe>& Animation::keyframes() const noexcept
{
    return _keyframes;
}

const Keyframe& Animation::current_keyframe() const noexcept
{
    return _keyframes[_current_keyframe];
}

void Animation::update(const TimeSpan& time, bool relativeToCurrentTime) noexcept
{
    auto currentTime = time;

    // Update the animation position.
    if (relativeToCurrentTime)
    {
        currentTime += _current_time;

        // If we reached the end, loop back to the start.
        if (currentTime >= duration())
        {
            currentTime       = 0;
            _current_time     = 0;
            _current_keyframe = 0;
        }
    }

    // _current_time = currentTime;
    _current_time = TimeSpan::from_seconds(Math::lerp(_current_time.total_seconds()
                                                    , currentTime.total_seconds()
                                                    , Math::pi / 16));

    while (_current_keyframe < _keyframes.size())
    {
        const auto& keyframe = _keyframes[_current_keyframe];

        // Stop when we've read up to the current time position.
        if (keyframe.time() > _current_time)
        {
            break;
        }

        ++_current_keyframe;
    }
}

}}
