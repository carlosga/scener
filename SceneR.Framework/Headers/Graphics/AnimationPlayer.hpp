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

#ifndef ANIMATIONPLAYER_HPP
#define ANIMATIONPLAYER_HPP

#include <Framework/Matrix.hpp>
#include <Graphics/AnimationClip.hpp>
#include <System/Core.hpp>
#include <System/TimeSpan.hpp>
#include <memory>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class SkinningData;

        class AnimationPlayer
        {
        public:
            AnimationPlayer(const std::shared_ptr<SkinningData>& skinningData);

            AnimationPlayer(const AnimationPlayer& animationPlayer);

            ~AnimationPlayer();

        public:
            /**
             * Starts decoding the specified animation clip.
             */
            void StartClip(const AnimationClip& clip);

            /**
             * Advances the current animation position.
             */
            void Update(const System::TimeSpan&          time
                      , const System::Boolean&           relativeToCurrentTime
                      , const SceneR::Framework::Matrix& rootTransform);

            /**
             * Helper used by the Update method to refresh the BoneTransforms data.
             */
            void UpdateBoneTransforms(const System::TimeSpan& time, const System::Boolean& relativeToCurrentTime);

            /**
             * Helper used by the Update method to refresh the WorldTransforms data.
             */
            void UpdateWorldTransforms(const SceneR::Framework::Matrix& rootTransform);

            /**
             * Helper used by the Update method to refresh the SkinTransforms data.
             */
            void UpdateSkinTransforms();

            /**
             * Gets the current bone transform matrices, relative to their parent bones.
             */
            const std::vector<SceneR::Framework::Matrix>& GetBoneTransforms() const;

            /**
             * Gets the current bone transform matrices, in absolute format.
             */
            const std::vector<SceneR::Framework::Matrix>& GetWorldTransforms() const;

            /**
             * Gets the current bone transform matrices,
             * relative to the skinning bind pose.
             */
            const std::vector<SceneR::Framework::Matrix>& GetSkinTransforms() const;

            /**
             * Gets the clip currently being decoded.
             */
            const AnimationClip& CurrentClip() const;

            /**
             * Gets the current play position.
             */
            const System::TimeSpan& CurrentTime() const;

        private:
            // Information about the currently playing animation clip.
            AnimationClip    currentClipValue;
            System::TimeSpan currentTimeValue;
            System::Size     currentKeyframe;

            // Backlink to the bind pose and skeleton hierarchy data.
            std::shared_ptr<SkinningData> skinningDataValue;

            // Current animation transform matrices.
            std::vector<SceneR::Framework::Matrix> boneTransforms;
            std::vector<SceneR::Framework::Matrix> worldTransforms;
            std::vector<SceneR::Framework::Matrix> skinTransforms;
        };
    }
}

#endif
