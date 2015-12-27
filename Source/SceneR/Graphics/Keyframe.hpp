// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_KEYFRAME_HPP
#define SCENER_GRAPHICS_KEYFRAME_HPP

#include "SceneR/Core/TimeSpan.hpp"
#include "SceneR/Math/Matrix.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class Keyframe
        {
        public:
            Keyframe();
            Keyframe(const SceneR::TimeSpan& time, const SceneR::Math::Matrix& transform);
            Keyframe(const Keyframe& keyframe) = default;

            ~Keyframe() = default;

        public:
            const SceneR::TimeSpan& time() const noexcept;

            const SceneR::Math::Matrix& transform() const noexcept;

        public:
            Keyframe& operator=(const Keyframe& keyframe) = default;

        private:
            SceneR::TimeSpan     _time;
            SceneR::Math::Matrix _transform;
        };
    }
}

#endif // SCENER_GRAPHICS_KEYFRAME_HPP
