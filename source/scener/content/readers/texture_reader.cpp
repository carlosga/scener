// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/texture_reader.hpp"

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/dds/surface.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/sampler_state.hpp"
#include "scener/graphics/texture2d.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::content::dds::surface;
    using scener::content::dds::surface_mipmap;
    using scener::graphics::igraphics_device_service;
    using scener::graphics::sampler_state;
    using scener::graphics::surface_format;
    using scener::graphics::texture2d;

    auto content_type_reader<texture2d>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto dds       = input->read_object<surface>(source["source"].get<std::string>());
        auto texture   = std::make_shared<texture2d>(gdservice->device(), dds->width(), dds->height(), dds->format());

        texture->name = key;

        texture->declare_storage(dds->mipmaps().size());

        for (const auto& mipmap : dds->mipmaps())
        {
            texture->set_data(mipmap.index(), mipmap.width(), mipmap.height(), mipmap.get_view());
        }

        texture->_sampler_state = input->read_object<sampler_state>(source["sampler"].get<std::string>());

        texture->_sampler_state->max_mip_level = texture->level_count();
        texture->_sampler_state->apply(texture->id());

        return texture;
    }
}

