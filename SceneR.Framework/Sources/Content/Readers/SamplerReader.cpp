// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/SamplerReader.hpp>

#include <json11.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/TextureAddressMode.hpp>
#include <Graphics/TextureFilter.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::SamplerState;
        using SceneR::Graphics::TextureAddressMode;
        using SceneR::Graphics::TextureFilter;
        using System::Text::Encoding;

        ContentTypeReader<SamplerState>::ContentTypeReader()
        {
        }

        ContentTypeReader<SamplerState>::~ContentTypeReader()
        {
        }

        std::shared_ptr<SamplerState> ContentTypeReader<SamplerState>::read(ContentReader*                      input
                                                                          , const std::pair<std::string, Json>& source)
        {
            auto& gdService = input->content_manager()->service_provider().get_service<IGraphicsDeviceService>();
            auto  sampler   = std::make_shared<SamplerState>(gdService.graphics_device());

            sampler->name       = Encoding::convert(source.first);
            sampler->mag_filter = static_cast<TextureFilter>(source.second["magFilter"].int_value());
            sampler->min_filter = static_cast<TextureFilter>(source.second["minFilter"].int_value());
            sampler->address_U  = static_cast<TextureAddressMode>(source.second["wrapS"].int_value());
            sampler->address_V  = static_cast<TextureAddressMode>(source.second["wrapT"].int_value());

            return sampler;
        }
    }
}

