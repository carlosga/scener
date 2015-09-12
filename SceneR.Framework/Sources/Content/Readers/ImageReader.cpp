// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ImageReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <System/IO/File.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Texture::Surface;
        using System::Text::Encoding;

        ContentTypeReader<Surface>::ContentTypeReader()
        {
        }

        ContentTypeReader<Surface>::~ContentTypeReader()
        {
        }

        std::shared_ptr<Surface> ContentTypeReader<Surface>::read(ContentReader*                      input
                                                                , const std::pair<std::string, Json>& source)
        {
            auto surface = std::make_shared<Surface>();

            surface->load(input->get_asset_path(Encoding::convert(source.second["uri"].string_value())));

            return surface;
        }
    }
}

