// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/ShaderIncludeReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Graphics/ShaderInclude.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Graphics::ShaderInclude;

auto ContentTypeReader<ShaderInclude>::read(ContentReader* input, const std::string& key, const Json& source) const
{
    auto uri  = source["uri"].string_value();
    auto code = input->read_external_reference(uri);
    auto path = source["rootPath"].string_value() + uri;
    auto sinc = std::make_shared<ShaderInclude>(key, path, code);

    sinc->declare();

    return sinc;
}

}}}

