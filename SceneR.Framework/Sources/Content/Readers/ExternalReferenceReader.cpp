// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ExternalReferenceReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using System::Text::Encoding;

        ContentTypeReader<std::vector<std::uint8_t>>::ContentTypeReader()
        {
        }

        ContentTypeReader<std::vector<std::uint8_t>>::~ContentTypeReader()
        {
        }

        std::shared_ptr<std::vector<std::uint8_t>> ContentTypeReader<std::vector<std::uint8_t>>::read(
            ContentReader* input, const std::pair<std::string, Json>& source)
        {
            auto contents = input->read_external_reference(Encoding::convert(source.second["uri"].string_value()));

            return std::make_shared<std::vector<std::uint8_t>>(contents.begin(), contents.end());
        }
    }
}

