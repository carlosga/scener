// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TextureReader.hpp>

#include <Content/json11.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/Texture2D.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::SamplerState;
        using SceneR::Graphics::SurfaceFormat;
        using SceneR::Graphics::Texture2D;
        using System::Text::Encoding;

        ContentTypeReader<Texture2D>::ContentTypeReader()
        {
        }

        ContentTypeReader<Texture2D>::~ContentTypeReader()
        {
        }

        std::shared_ptr<SceneR::Graphics::Texture2D> ContentTypeReader<Texture2D>::read(ContentReader*                      input
                                                                                      , const std::pair<std::string, Json>& source)
        {
            // TODO: Detect width and height, generate mipmaps and set texture data
            auto& gdService = input->content_manager()->service_provider().get_service<IGraphicsDeviceService>();
            auto  texture   = std::make_shared<Texture2D>(gdService.graphics_device(), 0, 0);
            auto  image     = input->read_external_reference(source.second["source"].string_value());

            // TODO: Read Sampler State reference
            // texture->name           = Encoding::convert(source.first);
            // texture->_sampler_state = context.find_object<SamplerState>(source.second["sampler"].string_value());

            switch (source.second["type"].int_value())
            {
            case 5121:  // (UNSIGNED_BYTE)
                texture->_format = SurfaceFormat::Color;
                break;
            case 33635: // (UNSIGNED_SHORT_5_6_5)
                texture->_format = SurfaceFormat::Bgr565;
                break;
            case 32819: // (UNSIGNED_SHORT_4_4_4_4)
                texture->_format = SurfaceFormat::Bgra4444;
                break;
            case 32820: // (UNSIGNED_SHORT_5_5_5_1)
                texture->_format = SurfaceFormat::Bgra5551;
                break;
            }

            // texture->set_data(image);

            return texture;
        }
    }
}

