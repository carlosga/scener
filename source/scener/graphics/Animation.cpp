// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/Animation.hpp"

namespace scener { namespace graphics {

using scener::timespan;

const timespan& Animation::current_time() const noexcept
{
    return _current_time;
}

const timespan& Animation::duration() const noexcept
{
    return _duration;
}

const std::vector<Keyframe>& Animation::keyframes() const noexcept
{
    return _keyframes;
}

const Keyframe& Animation::current_keyframe() const noexcept
{
    return _keyframes[_current_keyframe];
}

const std::string& Animation::name() const noexcept
{
    return _name;
}

void Animation::update(const timespan& time, bool relativeToCurrentTime) noexcept
{
    auto       currentTime = time;
    const auto count       = _keyframes.size();

    // Update the animation position.
    if (relativeToCurrentTime)
    {
        currentTime += _current_time;

        // If we reached the end, loop back to the start.
        if (currentTime >= _duration)
        {
            currentTime       = 0;
            _current_time     = 0;
            _current_keyframe = 0;
        }
    }

    _current_time = timespan::from_seconds(scener::math::lerp(_current_time.total_seconds()
                                                            , currentTime.total_seconds()
                                                            , scener::math::pi<double> / 16));

    while (_current_keyframe < count)
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
