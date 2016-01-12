// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/ImageReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/DDS/Surface.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Content::DDS::Surface;

auto ContentTypeReader<Surface>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto surface = std::make_shared<Surface>();

    surface->load(input->get_asset_path(source["uri"].string_value()));

    return surface;
}

}}}
