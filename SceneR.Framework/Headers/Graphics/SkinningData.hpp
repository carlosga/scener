// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-----------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef SKINNINGDATA_HPP
#define SKINNINGDATA_HPP

#include <map>
#include <string>
#include <vector>

#include <System/Core.hpp>
#include <Framework/Matrix.hpp>
#include <Graphics/AnimationClip.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class SkinningData
        {
        public:
            SkinningData();

            SkinningData(const std::map<std::u16string, AnimationClip>& animationClips
                       , const std::vector<SceneR::Framework::Matrix>&  bindPose
                       , const std::vector<SceneR::Framework::Matrix>&  inverseBindPose
                       , const std::vector<System::UInt32>&             skeletonHierarchy);

            SkinningData(const SkinningData& skinningData);

            /**
             * Destructor
             */
            ~SkinningData();

        public:
            const std::map<std::u16string, AnimationClip>& AnimationClips() const;

            const AnimationClip& AnimationClips(const std::u16string& clipName);

            const std::vector<SceneR::Framework::Matrix>& BindPose() const;

            const std::vector<SceneR::Framework::Matrix>& InverseBindPose() const;

            const std::vector<System::UInt32>& SkeletonHierarchy() const;

        private:
            std::map<std::u16string, AnimationClip> animationClips;
            std::vector<SceneR::Framework::Matrix>  bindPose;
            std::vector<SceneR::Framework::Matrix>  inverseBindPose;
            std::vector<System::UInt32>             skeletonHierarchy;
        };
    }
}

#endif
