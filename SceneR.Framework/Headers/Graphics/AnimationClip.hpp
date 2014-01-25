//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------
//
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef ANIMATIONCLIP_HPP
#define ANIMATIONCLIP_HPP

#include <Graphics/Keyframe.hpp>
#include <System/TimeSpan.hpp>
#include <vector>

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

            ~AnimationClip();

        public:
            const System::TimeSpan& Duration() const;

            const std::vector<Keyframe>& Keyframes() const;

        private:
            System::TimeSpan      duration;
            std::vector<Keyframe> keyframes;
        };
    }
}

#endif /* ANIMATIONCLIP_HPP */
