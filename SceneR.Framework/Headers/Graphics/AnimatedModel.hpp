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

#ifndef ANIMATEDMODEL_HPP
#define ANIMATEDMODEL_HPP

#include <Graphics/Model.hpp>
#include <Graphics/AnimationPlayer.hpp>
#include <Graphics/SkinningData.hpp>
#include <System/Core.hpp>
#include <memory>

namespace SceneR
{
    namespace Framework
    {
        class RenderTime;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class AnimatedModel
        {
        public:
            AnimatedModel(const std::shared_ptr<Model>& model);
            virtual ~AnimatedModel();

        public:
            /**
             * Starts playing an animation clip by its name. The default animation clip
             * in FBX models is called "Take 001" and therefore is default value of the
             * clipName parameter. Starting the clip doesn't have any effect on the displayed
             * model until the animation is updated (via Update()).
             * @param clipName name of the animation clip
             */
            void Play(const System::String& clipName = u"Take 001");

            /**
             * Plays the first clip.
             */
            void PlayFirstClip();

            /**
             * Advances the animation by given time and updates the model
             * skin accordingly.
             * @param renderTime elapsed time
             */
            void Update(const SceneR::Framework::RenderTime& renderTime);

            /**
             * Draws the animated model's transformed skin with regard to any currently playing
             * animation.
             * @param world world transform
             * @param view camera view transform
             * @param projection camera projection transform
             */
            void Draw(const SceneR::Framework::Matrix& world
                    , const SceneR::Framework::Matrix& view
                    , const SceneR::Framework::Matrix& projection);

        protected:
            /**
             * The animated model itself
             */
            std::shared_ptr<Model> model;

            /**
             * The underlying skinning data including bone weights and indices
             * for skinned mesh animation.
             */
            SkinningData skinningData;

            /**
             * Animation Controller that is used to apply animations to the model
             */
            AnimationPlayer player;
        };
    }
}

#endif /* ANIMATEDMODEL_HPP */
