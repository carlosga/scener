// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Keyframe.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::TimeSpan;
        using SceneR::Framework::Matrix;

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
