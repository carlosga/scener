// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <Graphics/AnimationClip.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::TimeSpan;

        AnimationClip::AnimationClip()
            : duration  { TimeSpan::Zero }
            , keyframes ( 0 )
        {
        }

        AnimationClip::AnimationClip(const TimeSpan& duration, const std::vector<Keyframe>& keyframes)
            : duration  { duration }
            , keyframes ( keyframes )
        {
        }

        AnimationClip::AnimationClip(const AnimationClip& clip)
            : duration  { clip.duration }
            , keyframes ( clip.keyframes )
        {
        }

        AnimationClip::~AnimationClip()
        {
        }

        const TimeSpan& AnimationClip::Duration() const
        {
            return this->duration;
        }

        const std::vector<Keyframe>& AnimationClip::Keyframes() const
        {
            return this->keyframes;
        }

        AnimationClip &AnimationClip::operator=(const AnimationClip& clip)
        {
            if (this != &clip)
            {
                this->duration  = clip.duration;
                this->keyframes = std::vector<Keyframe>(clip.keyframes);
            }

            return *this;
        }
    }
}
