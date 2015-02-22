// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef ANIMATIONCLIP_HPP
#define ANIMATIONCLIP_HPP

#include <vector>

#include <Graphics/Keyframe.hpp>
#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * An animation clip is the runtime equivalent of the
         * Microsoft.Xna.Framework.Content.Pipeline.Graphics.AnimationContent type.
         * It holds all the keyframes needed to describe a single animation.
         */
        class AnimationClip
        {
        public:
            AnimationClip();
            AnimationClip(const System::TimeSpan& duration, const std::vector<Keyframe>& keyframes);
            AnimationClip(const AnimationClip& clip);
            ~AnimationClip() = default;

        public:
            const System::TimeSpan& Duration() const;
            const std::vector<Keyframe>& Keyframes() const;

        public:
            AnimationClip& operator=(const AnimationClip& clip);

        private:
            System::TimeSpan      duration;
            std::vector<Keyframe> keyframes;
        };
    }
}

#endif /* ANIMATIONCLIP_HPP */
