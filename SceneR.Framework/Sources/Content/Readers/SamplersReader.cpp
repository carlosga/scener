// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/SamplersReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/TextureAddressMode.hpp>
#include <Graphics/TextureFilter.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::SamplerState;
        using SceneR::Graphics::TextureAddressMode;
        using SceneR::Graphics::TextureFilter;
        using System::Text::Encoding;

        SamplersReader::SamplersReader()
        {

        }

        SamplersReader::~SamplersReader()
        {

        }

        void SamplersReader::read(const json11::Json& value, ContentReaderContext& context)
        {
            for (const auto& source : value["samplers"].object_items())
            {
                auto sampler = std::make_shared<SamplerState>(context.graphics_device);

                sampler->name       = Encoding::convert(source.first);
                sampler->mag_filter = static_cast<TextureFilter>(source.second["magFilter"].int_value());
                sampler->min_filter = static_cast<TextureFilter>(source.second["minFilter"].int_value());
                sampler->address_U  = static_cast<TextureAddressMode>(source.second["wrapS"].int_value());
                sampler->address_V  = static_cast<TextureAddressMode>(source.second["wrapT"].int_value());

                context.samplers.push_back(sampler);
            }
        }
    }
}

