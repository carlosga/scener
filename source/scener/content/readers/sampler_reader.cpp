// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/sampler_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/sampler_state.hpp"

namespace scener::content::readers
{
    using json11::Json;
    using scener::graphics::igraphics_device_service;
    using scener::graphics::sampler_state;
    using scener::graphics::texture_address_mode;
    using scener::graphics::texture_filter;

    auto content_type_reader<sampler_state>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
    {
        auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto sampler   = std::make_shared<sampler_state>(gdservice->device());

        sampler->name       = key;
        sampler->mag_filter = static_cast<texture_filter>(source["magFilter"].int_value());
        sampler->min_filter = static_cast<texture_filter>(source["minFilter"].int_value());
        sampler->address_u  = static_cast<texture_address_mode>(source["wrapS"].int_value());
        sampler->address_v  = static_cast<texture_address_mode>(source["wrapT"].int_value());

        return sampler;
    }
}

