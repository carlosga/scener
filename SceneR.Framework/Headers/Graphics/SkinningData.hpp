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

#ifndef SKINNINGDATA_HPP
#define SKINNINGDATA_HPP

#include <Framework/Matrix.hpp>
#include <Graphics/AnimationClip.hpp>
#include <System/Core.hpp>
#include <map>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class SkinningData
        {
        public:
            SkinningData();
            SkinningData(std::map<System::String, AnimationClip> animationClips
                       , std::vector<SceneR::Framework::Matrix>  bindPose
                       , std::vector<SceneR::Framework::Matrix>  inverseBindPose
                       , std::vector<System::Int32>              skeletonHierarchy);

            virtual ~SkinningData();

        public:
            std::map<System::String, AnimationClip>& AnimationClips();

            std::vector<SceneR::Framework::Matrix>& BindPose();

            const std::vector<SceneR::Framework::Matrix>& InverseBindPose() const;

            const std::vector<System::Int32>& SkeletonHierarchy() const;

        private:
            std::map<System::String, AnimationClip> animationClips;
            std::vector<SceneR::Framework::Matrix>  bindPose;
            std::vector<SceneR::Framework::Matrix>  inverseBindPose;
            std::vector<System::Int32>              skeletonHierarchy;
        };
    }
}

#endif
