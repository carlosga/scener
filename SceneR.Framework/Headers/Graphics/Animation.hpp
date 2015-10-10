// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_ANIMATION_HPP
#define GRAPHICS_ANIMATION_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <Graphics/Keyframe.hpp>
#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class Animation final
        {
        public:
            Animation();
            ~Animation() = default;

        public:
            const System::TimeSpan& current_time() const noexcept;
            const System::TimeSpan& duration() const noexcept;
            const std::string& name() const noexcept;
            const std::vector<Keyframe>& keyframes() const noexcept;
            std::size_t current_keyframe() const noexcept;

            void update(const System::TimeSpan& time, const bool& relativeToCurrentTime) noexcept;
            void advance() noexcept;

        private:
            std::string           _name;
            std::vector<Keyframe> _keyframes;
            System::TimeSpan      _current_time;
            std::size_t           _current_keyframe;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif // GRAPHICS_ANIMATION_HPP
