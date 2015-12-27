// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/SamplerReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentManager.hpp"
#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Graphics/IGraphicsDeviceService.hpp"
#include "SceneR/Graphics/RendererServiceContainer.hpp"
#include "SceneR/Graphics/TextureAddressMode.hpp"
#include "SceneR/Graphics/TextureFilter.hpp"

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::SamplerState;
        using SceneR::Graphics::TextureAddressMode;
        using SceneR::Graphics::TextureFilter;

        std::shared_ptr<SamplerState> ContentTypeReader<SamplerState>::read(gsl::not_null<ContentReader*>       input
                                                                          , const std::pair<std::string, Json>& source) const
        {
            auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
            auto sampler   = std::make_shared<SamplerState>(gdService->graphics_device());

            sampler->name       = source.first;
            sampler->mag_filter = static_cast<TextureFilter>(source.second["magFilter"].int_value());
            sampler->min_filter = static_cast<TextureFilter>(source.second["minFilter"].int_value());
            sampler->address_u  = static_cast<TextureAddressMode>(source.second["wrapS"].int_value());
            sampler->address_v  = static_cast<TextureAddressMode>(source.second["wrapT"].int_value());

            return sampler;
        }
    }
}

