// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_KEYFRAME_HPP
#define GRAPHICS_KEYFRAME_HPP

#include <System/TimeSpan.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Keyframe
        {
        public:
            Keyframe();
            Keyframe(const System::TimeSpan& time, const SceneR::Framework::Matrix& transform);
            Keyframe(const Keyframe& keyframe) = default;

            ~Keyframe() = default;

        public:
            const System::TimeSpan& time() const noexcept;

            const SceneR::Framework::Matrix& transform() const noexcept;

        public:
            Keyframe& operator=(const Keyframe& keyframe) = default;

        private:
            System::TimeSpan           _time;
            SceneR::Framework::Matrix  _transform;
        };
    }
}

#endif  // GRAPHICS_KEYFRAME_HPP
