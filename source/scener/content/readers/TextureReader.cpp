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
using scener::graphics::IGraphicsDeviceService;
using scener::graphics::SamplerState;
using scener::graphics::SurfaceFormat;
using scener::graphics::Texture2D;

auto ContentTypeReader<Texture2D>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
    auto dds       = input->read_object<surface>(source["source"].string_value());
    auto texture   = std::make_shared<Texture2D>(gdService->graphics_device()
                                               , dds->width()
                                               , dds->height()
                                               , dds->format());

    texture->name = key;

    texture->declare_storage(dds->mipmaps().size());

    for (const auto& mipmap : dds->mipmaps())
    {
        texture->set_data(mipmap.index(), mipmap.width(), mipmap.height(), mipmap.get_view());
    }

    texture->_sampler_state = input->read_object<SamplerState>(source["sampler"].string_value());

    texture->_sampler_state->max_mip_level = texture->level_count();
    texture->_sampler_state->apply(texture->id());

    return texture;
}

}}}

