// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ImagesReader.hpp>

#include <Content/json11.hpp>
#include <Content/ContentReader.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::Text::Encoding;

        ImagesReader::ImagesReader()
        {

        }

        ImagesReader::~ImagesReader()
        {

        }

        void ImagesReader::read(const json11::Json& value, ContentReaderContext& context)
        {
            for (const auto& source : value["images"].object_items())
            {
                auto image  = Encoding::convert(source.second["uri"].string_value());
                auto buffer = context.content_reader->read_external_reference(image);

                context.images[source.first] = buffer;
            }
        }
    }
}
