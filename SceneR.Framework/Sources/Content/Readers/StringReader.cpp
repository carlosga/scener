// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/StringReader.hpp>

#include <string>

#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        StringReader::StringReader()
        {
        }

        StringReader::~StringReader()
        {
        }

        std::shared_ptr<void> StringReader::Read(ContentReader& input)
        {
            return std::make_shared<std::u16string>(input.ReadString());
        }
    }
}
