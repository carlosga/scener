// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/SamplerState.hpp"

#include "scener/graphics/GraphicsDevice.hpp"

namespace scener { namespace graphics {

sampler_state::sampler_state(gsl::not_null<graphics::graphics_device*> device) noexcept
    : graphics_resource { device }
{
}

void sampler_state::apply(std::uint32_t texture_id) const noexcept
{
    glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S    , static_cast<GLint>(address_u));
    glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T    , static_cast<GLint>(address_v));
    glTextureParameteri(texture_id, GL_TEXTURE_WRAP_R    , static_cast<GLint>(address_w));
    glTextureParameteri(texture_id, GL_TEXTURE_MAX_LEVEL , static_cast<GLint>(max_mip_level));
    glTextureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(min_filter));
    glTextureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(mag_filter));
    glTextureParameterf(texture_id, GL_TEXTURE_LOD_BIAS  , mip_map_level_of_detail_bias);
}

}}
