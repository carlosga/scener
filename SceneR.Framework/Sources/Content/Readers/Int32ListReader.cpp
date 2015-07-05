// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/Int32ListReader.hpp>

#include <cstdint>

#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;

Int32ListReader::Int32ListReader()
{
}

Int32ListReader::~Int32ListReader()
{
}

std::shared_ptr<void> Int32ListReader::Read(ContentReader& input)
{
    auto values = std::make_shared<std::vector<std::uint32_t>>();
    auto count  = input.ReadUInt32();

    values->reserve(count);

    for (std::uint32_t i = 0; i < count; i++)
    {
        values->push_back(input.ReadUInt32());
    }

    return values;
}
