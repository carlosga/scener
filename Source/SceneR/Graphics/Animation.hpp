// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_ANIMATION_HPP
#define SCENER_GRAPHICS_ANIMATION_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "SceneR/Graphics/Keyframe.hpp"

namespace SceneR { namespace Content { namespace Readers {

template <typename T> class ContentTypeReader;

}}}

namespace SceneR
{
    namespace Graphics
    {
        class Animation final
        {
        public:
            Animation();
            ~Animation() = default;

        public:
            const SceneR::TimeSpan& current_time() const noexcept;
            const SceneR::TimeSpan& duration() const noexcept;
            const std::string& name() const noexcept;
            const std::vector<Keyframe>& keyframes() const noexcept;
            const Keyframe& current_keyframe() const noexcept;

            void update(const SceneR::TimeSpan& time, const bool& relativeToCurrentTime) noexcept;

        private:
            std::string           _name;
            std::vector<Keyframe> _keyframes;
            SceneR::TimeSpan      _current_time;
            std::size_t           _current_keyframe;

            template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
        };
    }
}

#endif // SCENER_GRAPHICS_ANIMATION_HPP
