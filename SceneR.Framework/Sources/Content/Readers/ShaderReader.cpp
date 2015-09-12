// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ShaderReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/ShaderType.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Shader;
        using SceneR::Graphics::ShaderType;
        using System::Text::Encoding;

        ContentTypeReader<Shader>::ContentTypeReader()
        {
        }

        ContentTypeReader<Shader>::~ContentTypeReader()
        {
        }

        std::shared_ptr<Shader> ContentTypeReader<Shader>::read(ContentReader*                      input
                                                              , const std::pair<std::string, Json>& source)
        {
            auto name   = Encoding::convert(source.first);
            auto type   = static_cast<ShaderType>(source.second["type"].int_value());
            auto uri    = Encoding::convert(source.second["uri"].string_value());
            auto code   = input->read_external_reference(uri);
            auto shader = std::make_shared<Shader>(name, type, code);

            shader->compile();

            return shader;
        }
    }
}

