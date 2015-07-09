// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AnimationClipReader.hpp>

#include <vector>

#include <Content/ContentReader.hpp>
#include <Graphics/AnimationClip.hpp>
#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::TimeSpan;
        using SceneR::Graphics::AnimationClip;
        using SceneR::Graphics::Keyframe;

        AnimationClipReader::AnimationClipReader()
        {
        }

        AnimationClipReader::~AnimationClipReader()
        {
        }

        std::shared_ptr<void> AnimationClipReader::Read(ContentReader& input)
        {
            return std::make_shared<AnimationClip>(TimeSpan { input.ReadInt64() }
                                                 , *input.ReadObject<std::vector<Keyframe>>());
        }
    }
}
