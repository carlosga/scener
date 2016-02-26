// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/TextureReader.hpp"

#include <json11.hpp>

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/dds/surface.hpp"
#include "scener/graphics/IGraphicsDeviceService.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/graphics/SamplerState.hpp"
#include "scener/graphics/Texture2D.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::dds::surface;
using scener::content::dds::surface_mipmap;
using scener::graphics::igraphics_device_service;
using scener::graphics::sampler_state;
using scener::graphics::surface_format;
using scener::graphics::texture2d;

auto content_type_reader<texture2d>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
    auto dds       = input->read_object<surface>(source["source"].string_value());
    auto texture   = std::make_shared<texture2d>(gdService->device()
                                               , dds->width()
                                               , dds->height()
                                               , dds->format());

    texture->name = key;

    texture->declare_storage(dds->mipmaps().size());

    for (const auto& mipmap : dds->mipmaps())
    {
        texture->set_data(mipmap.index(), mipmap.width(), mipmap.height(), mipmap.get_view());
    }

    texture->_sampler_state = input->read_object<sampler_state>(source["sampler"].string_value());

    texture->_sampler_state->max_mip_level = texture->level_count();
    texture->_sampler_state->apply(texture->id());

    return texture;
}

}}}

