// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/image_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/dds/surface.hpp"
#include "scener/content/gltf/constants.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::content::dds::surface;
    using namespace scener::content::gltf;

    auto content_type_reader<surface>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<surface>();

        instance->load(input->get_asset_path(value[k_uri].get<std::string>()));

        return instance;
    }
}
