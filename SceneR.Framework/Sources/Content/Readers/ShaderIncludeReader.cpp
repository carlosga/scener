// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ShaderIncludeReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::ShaderInclude;

        std::shared_ptr<ShaderInclude> ContentTypeReader<ShaderInclude>::read(Guide::not_null<ContentReader*>     input
                                                                            , const std::pair<std::string, Json>& source) const
        {
            auto name = source.first;
            auto uri  = source.second["uri"].string_value();
            auto code = input->read_external_reference(uri);
            auto path = source.second["rootPath"].string_value() + uri;
            auto sinc = std::make_shared<ShaderInclude>(name, path, code);

            sinc->declare();

            return sinc;
        }
    }
}

