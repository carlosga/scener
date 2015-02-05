// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/KeyframeReader.hpp>

#include <Graphics/Keyframe.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

std::shared_ptr<void> KeyframeReader::Read(ContentReader& input)
{
    return std::make_shared<Keyframe>(input.ReadInt32()
                                    , TimeSpan { input.ReadInt64() }
                                    , input.ReadMatrix());
}
