// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/KeyframeListReader.hpp>

#include <Content/ContentReader.hpp>
#include <Graphics/Keyframe.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

KeyframeListReader::KeyframeListReader()
{
}

KeyframeListReader::~KeyframeListReader()
{
}

std::shared_ptr<void> KeyframeListReader::Read(ContentReader& input)
{
    auto keyframes     = std::make_shared<std::vector<Keyframe>>();
    auto keyframeCount = input.ReadUInt32();

    keyframes->reserve(keyframeCount);

    for (uint32_t i = 0; i < keyframeCount; i++)
    {
        keyframes->push_back(*input.ReadObject<Keyframe>());
    }

    return keyframes;
}
