// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/ImageReader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/dds/surface.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::dds::surface;

auto content_type_reader<surface>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto image = std::make_shared<surface>();

    image->load(input->get_asset_path(source["uri"].string_value()));

    return image;
}

}}}
