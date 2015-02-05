// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/StringReader.hpp>

#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;

std::shared_ptr<void> StringReader::Read(ContentReader& input)
{
    auto tmp = input.ReadString();

    return std::make_shared<String>(tmp.begin(), tmp.end());
}
