// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Keyframe.hpp"

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::TimeSpan;
        using SceneR::Math::Matrix;

        Keyframe::Keyframe()
            : Keyframe { TimeSpan::zero, Matrix::identity }
        {
        }

        Keyframe::Keyframe(const TimeSpan& time, const Matrix& transform)
            : _time      { time }
            , _transform { transform }
        {
        }

        const TimeSpan& Keyframe::time() const noexcept
        {
            return _time;
        }

        const Matrix& Keyframe::transform() const noexcept
        {
            return _transform;
        }
    }
}
