// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/Int32Reader.hpp>

#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;

std::shared_ptr<void> Int32Reader::Read(ContentReader& input)
{
    return std::make_shared<Int32>(input.ReadInt32());
}
