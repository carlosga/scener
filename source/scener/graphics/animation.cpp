// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/animation.hpp"

namespace scener::graphics
{
    using scener::timespan;

    const timespan& animation::current_time() const noexcept
    {
        return _current_time;
    }

    const timespan& animation::duration() const noexcept
    {
        return _duration;
    }

    const std::vector<keyframe>& animation::keyframes() const noexcept
    {
        return _keyframes;
    }

    const keyframe& animation::current_keyframe() const noexcept
    {
        return _keyframes[_current_keyframe];
    }

    const std::string& animation::name() const noexcept
    {
        return _name;
    }

    void animation::update(const timespan& time, bool relative) noexcept
    {
        auto       current_time = time;
        const auto count        = _keyframes.size();

        // Update the animation position.
        if (relative)
        {
            current_time += _current_time;

            // If we reached the end, loop back to the start.
            if (current_time >= _duration)
            {
                current_time       = 0;
                _current_time     = 0;
                _current_keyframe = 0;
            }
        }

        _current_time = timespan::from_seconds(scener::math::lerp(_current_time.total_seconds()
                                                                 , current_time.total_seconds()
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
}
