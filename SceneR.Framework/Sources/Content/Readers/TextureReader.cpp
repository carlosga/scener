// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TextureReader.hpp>

#include <json11.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/Texture2D.hpp>
#include <Texture/Surface.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::SamplerState;
        using SceneR::Graphics::SurfaceFormat;
        using SceneR::Graphics::Texture2D;
        using SceneR::Texture::Surface;
        using SceneR::Texture::SurfaceMipmap;

        std::shared_ptr<Texture2D> ContentTypeReader<Texture2D>::read(gsl::not_null<ContentReader*>       input
                                                                    , const std::pair<std::string, Json>& source) const
        {
            auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
            auto surface   = input->read_object<Surface>("images", source.second["source"].string_value());
            auto texture   = std::make_shared<Texture2D>(gdService->graphics_device()
                                                        , surface->width()
                                                        , surface->height()
                                                        , surface->mipmaps().size()
                                                        , surface->format());

            texture->declare_storage(surface->mipmaps().size());

            texture->name           = source.first;
            texture->_sampler_state = input->read_object<SamplerState>("samplers", source.second["sampler"].string_value());

            texture->_sampler_state->max_mip_level = texture->level_count();
            texture->_sampler_state->apply(texture->id());

            for (const auto& mipmap : surface->mipmaps())
            {
                texture->set_data(mipmap.index(), mipmap.width(), mipmap.height(), mipmap.get_data());
            }

            return texture;
        }
    }
}

