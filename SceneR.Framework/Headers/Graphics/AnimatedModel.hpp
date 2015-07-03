// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#ifndef ANIMATEDMODEL_HPP
#define ANIMATEDMODEL_HPP

#include <memory>
#include <string>

#include <Graphics/AnimationPlayer.hpp>

namespace SceneR
{
    namespace Framework
    {
        class RenderTime;
        struct Matrix;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Model;
        class SkinningData;

        class AnimatedModel
        {
        public:
            AnimatedModel(const std::shared_ptr<Model>& model);

            ~AnimatedModel();

        public:
            /**
             * Starts playing an animation clip by its name. The default animation clip
             * in FBX models is called "Take 001" and therefore is default value of the
             * clipName parameter. Starting the clip doesn't have any effect on the displayed
             * model until the animation is updated (via Update()).
             * @param clipName name of the animation clip
             */
            void Play(const std::u16string& clipName = u"Take 001");

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
            std::shared_ptr<SkinningData> skinningData;

            /**
             * Animation Controller that is used to apply animations to the model
             */
            AnimationPlayer player;
        };
    }
}

#endif /* ANIMATEDMODEL_HPP */
