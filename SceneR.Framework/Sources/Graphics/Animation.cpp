// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Animation.hpp>

#include <functional>
#include <gsl.h>

namespace SceneR
{
    namespace Graphics
    {
        using System::TimeSpan;

        Animation::Animation()
            : _name()
            , _keyframes(0)
            , _current_time(0)
            , _current_keyframe(0)
        {
        }

        const System::TimeSpan& Animation::current_time() const noexcept
        {
            return _current_time;
        }

        const System::TimeSpan& Animation::duration() const noexcept
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

        std::size_t Animation::current_keyframe() const noexcept
        {
            return _current_keyframe;
        }

        void Animation::update(const TimeSpan& time, const bool& relativeToCurrentTime) noexcept
        {
            auto currentTime = time;

            // Update the animation position.
            if (relativeToCurrentTime)
            {
                currentTime += _current_time;

                // If we reached the end, loop back to the start.
                while (currentTime >= duration())
                {
                    currentTime = 0;
                }
            }

            Ensures((currentTime > TimeSpan::zero) || (currentTime <= duration()));

            // If the position moved backwards, reset the keyframe index.
            if (currentTime < _current_time)
            {
                _current_keyframe = 0;
            }

            _current_time = currentTime;
        }

        void Animation::advance() noexcept
        {
            ++_current_keyframe;
        }
    }
}