// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TextureReader.hpp>

#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        TextureReader::TextureReader()
        {
        }

        TextureReader::~TextureReader()
        {
        }

        std::shared_ptr<void> TextureReader::Read(ContentReader& input)
        {
            // Never directly invoked (as Texture is an abstract base type),
            // but sometimes referenced in .xnb headers as a base reader for polymorphic values.
            return nullptr;
        }
    }
}
