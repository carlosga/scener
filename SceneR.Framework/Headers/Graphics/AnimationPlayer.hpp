// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef ANIMATIONPLAYER_HPP
#define ANIMATIONPLAYER_HPP

#include <memory>
#include <vector>

#include <Framework/Matrix.hpp>
#include <Graphics/AnimationClip.hpp>
#include <System/TimeSpan.hpp>

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

            ~AnimationPlayer() = default;

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
