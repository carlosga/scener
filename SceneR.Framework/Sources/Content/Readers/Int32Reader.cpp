// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/Int32Reader.hpp>

#include <cstdint>

#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        Int32Reader::Int32Reader()
        {
        }

        Int32Reader::~Int32Reader()
        {
        }

        std::shared_ptr<void> Int32Reader::Read(ContentReader& input)
        {
            return std::make_shared<std::uint32_t>(input.ReadUInt32());
        }
    }
}
