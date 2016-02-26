// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/SamplerReader.hpp"

#include <json11.hpp>

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/graphics/IGraphicsDeviceService.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/graphics/SamplerState.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::graphics::igraphics_device_service;
using scener::graphics::sampler_state;
using scener::graphics::texture_address_mode;
using scener::graphics::texture_filter;

auto ContentTypeReader<sampler_state>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
    auto sampler   = std::make_shared<sampler_state>(gdService->device());

    sampler->name       = key;
    sampler->mag_filter = static_cast<texture_filter>(source["magFilter"].int_value());
    sampler->min_filter = static_cast<texture_filter>(source["minFilter"].int_value());
    sampler->address_u  = static_cast<texture_address_mode>(source["wrapS"].int_value());
    sampler->address_v  = static_cast<texture_address_mode>(source["wrapT"].int_value());

    return sampler;
}

}}}

