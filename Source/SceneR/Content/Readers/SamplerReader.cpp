// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/SamplerReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentManager.hpp"
#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Graphics/IGraphicsDeviceService.hpp"
#include "SceneR/Graphics/RendererServiceContainer.hpp"
#include "SceneR/Graphics/SamplerState.hpp"
#include "SceneR/Graphics/TextureAddressMode.hpp"
#include "SceneR/Graphics/TextureFilter.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Graphics::IGraphicsDeviceService;
using SceneR::Graphics::SamplerState;
using SceneR::Graphics::TextureAddressMode;
using SceneR::Graphics::TextureFilter;

auto ContentTypeReader<SamplerState>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
    auto sampler   = std::make_shared<SamplerState>(gdService->graphics_device());

    sampler->name       = key;
    sampler->mag_filter = static_cast<TextureFilter>(source["magFilter"].int_value());
    sampler->min_filter = static_cast<TextureFilter>(source["minFilter"].int_value());
    sampler->address_u  = static_cast<TextureAddressMode>(source["wrapS"].int_value());
    sampler->address_v  = static_cast<TextureAddressMode>(source["wrapT"].int_value());

    return sampler;
}

}}}

