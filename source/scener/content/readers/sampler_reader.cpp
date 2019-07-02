// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/sampler_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/sampler_state.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::sampler_state;
    using scener::graphics::texture_address_mode;
    using scener::graphics::texture_filter;
    using namespace scener::content::gltf;

    auto content_type_reader<sampler_state>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto sampler = std::make_shared<sampler_state>();

        // sampler->name       = key;
        sampler->mag_filter = static_cast<texture_filter>(value[k_mag_filter].get<std::int32_t>());
        sampler->min_filter = static_cast<texture_filter>(value[k_min_filter].get<std::int32_t>());
        sampler->address_u  = static_cast<texture_address_mode>(value[k_wrap_s].get<std::int32_t>());
        sampler->address_v  = static_cast<texture_address_mode>(value[k_wrap_t].get<std::int32_t>());

        return sampler;
    }
}

