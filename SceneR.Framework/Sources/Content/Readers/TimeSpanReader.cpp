// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TimeSpanReader.hpp>

#include <System/TimeSpan.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;

TimeSpanReader::TimeSpanReader()
{
}

TimeSpanReader::~TimeSpanReader()
{
}

std::shared_ptr<void> TimeSpanReader::Read(ContentReader& input)
{
    return std::make_shared<TimeSpan>(input.ReadUInt64());
}
