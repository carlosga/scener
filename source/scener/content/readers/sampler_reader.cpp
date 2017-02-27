// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/sampler_reader.hpp"

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/sampler_state.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::igraphics_device_service;
    using scener::graphics::sampler_state;
    using scener::graphics::texture_address_mode;
    using scener::graphics::texture_filter;
    using namespace scener::content::gltf;

    auto content_type_reader<sampler_state>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto sampler   = std::make_shared<sampler_state>(gdservice->device());

        sampler->name       = key;
        sampler->mag_filter = static_cast<texture_filter>(source[k_mag_filter].get<std::int32_t>());
        sampler->min_filter = static_cast<texture_filter>(source[k_min_filter].get<std::int32_t>());
        sampler->address_u  = static_cast<texture_address_mode>(source[k_wrap_s].get<std::int32_t>());
        sampler->address_v  = static_cast<texture_address_mode>(source[k_wrap_t].get<std::int32_t>());

        return sampler;
    }
}

