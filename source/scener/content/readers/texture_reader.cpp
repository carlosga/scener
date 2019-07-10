// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/texture_reader.hpp"

#include <vulkan/vulkan.hpp>

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/dds/surface.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/sampler_state.hpp"
#include "scener/graphics/texture2d.hpp"
#include "scener/graphics/texture_target.hpp"
#include "scener/graphics/vulkan/image_options.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::content::dds::surface;
    using scener::content::dds::surface_mipmap;
    using scener::graphics::igraphics_device_service;
    using scener::graphics::sampler_state;
    using scener::graphics::surface_format;
    using scener::graphics::texture2d;
    using scener::graphics::texture_target;
    using scener::graphics::vulkan::image_options;
    using namespace scener::content::gltf;

    auto content_type_reader<texture2d>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        const auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        const auto device    = gdservice->device();
        const auto dds       = input->read_object<surface>(value[k_source].get<std::string>());
        const auto sstate    = input->read_object<sampler_state>(value[k_sampler].get<std::string>());

        auto instance = std::make_shared<texture2d>(gdservice->device(), dds->width(), dds->height(), dds->format());

        instance->name           = key;
        instance->_mipmap_levels = static_cast<std::uint32_t>(dds->mipmaps().size());
        instance->_sampler       = device->create_sampler(*sstate.get());
        sstate->max_mip_level    = instance->level_count();

        image_options options;

        options.usage      = vk::ImageUsageFlagBits::eSampled;
        options.extent     = vk::Extent3D(dds->width(), dds->height());
        options.mip_levels = static_cast<std::uint32_t>(dds->mipmaps().size());
        options.target     = texture_target::texture_buffer;

        instance->_storage = device->create_image(options);

        // instance->_storage.set_data()

        for (const auto& mipmap : dds->mipmaps())
        {
            instance->set_data(mipmap.index(), mipmap.width(), mipmap.height(), mipmap.get_view());
        }

        return instance;
    }
}
