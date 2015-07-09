// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AnimationClipMapReader.hpp>

#include <cstdint>
#include <map>
#include <string>

#include <Content/ContentReader.hpp>
#include <Graphics/AnimationClip.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::AnimationClip;

        AnimationClipMapReader::AnimationClipMapReader()
        {
        }

        AnimationClipMapReader::~AnimationClipMapReader()
        {
        }

        std::shared_ptr<void> AnimationClipMapReader::Read(ContentReader& input)
        {
            auto clipCount      = input.ReadUInt32();
            auto animationClips = std::make_shared<std::map<std::u16string, AnimationClip>>();

            for (std::uint32_t i = 0; i < clipCount; i++)
            {
                auto clipName = *input.ReadObject<std::u16string>();

                animationClips->emplace(clipName, *input.ReadObject<AnimationClip>());
            }

            return animationClips;
        }
    }
}
