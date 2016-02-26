// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/TextureReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentManager.hpp"
#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/DDS/Surface.hpp"
#include "SceneR/Graphics/IGraphicsDeviceService.hpp"
#include "SceneR/Graphics/RendererServiceContainer.hpp"
#include "SceneR/Graphics/SamplerState.hpp"
#include "SceneR/Graphics/Texture2D.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::dds::Surface;
using scener::content::dds::SurfaceMipmap;
using scener::graphics::IGraphicsDeviceService;
using scener::graphics::SamplerState;
using scener::graphics::SurfaceFormat;
using scener::graphics::Texture2D;

auto ContentTypeReader<Texture2D>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
    auto surface   = input->read_object<Surface>(source["source"].string_value());
    auto texture   = std::make_shared<Texture2D>(gdService->graphics_device()
                                               , surface->width()
                                               , surface->height()
                                               , surface->format());

    texture->name = key;

    texture->declare_storage(surface->mipmaps().size());

    for (const auto& mipmap : surface->mipmaps())
    {
        texture->set_data(mipmap.index(), mipmap.width(), mipmap.height(), mipmap.get_view());
    }

    texture->_sampler_state = input->read_object<SamplerState>(source["sampler"].string_value());

    texture->_sampler_state->max_mip_level = texture->level_count();
    texture->_sampler_state->apply(texture->id());

    return texture;
}

}}}

