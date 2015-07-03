// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/DictionaryReader.hpp>

#include <map>

#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;

DictionaryReader::DictionaryReader()
{
}

DictionaryReader::~DictionaryReader()
{
}

std::shared_ptr<void> DictionaryReader::Read(ContentReader& input)
{
    auto dictionary = std::make_shared<std::map<std::u16string, std::shared_ptr<void>>>();
    auto count      = input.ReadUInt32();

    for (UInt32 i = 0; i < count; i++)
    {
        auto key   = *input.ReadObject<std::u16string>();
        auto value = nullptr; //input.ReadObject();

        dictionary->emplace(key, value);
    }

    return dictionary;
}
