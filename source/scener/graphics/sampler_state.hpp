// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SAMPLER_STATE_HPP
#define SCENER_GRAPHICS_SAMPLER_STATE_HPP

#include <cstddef>
#include <cstdint>

#include "scener/graphics/texture_filter.hpp"
#include "scener/graphics/texture_address_mode.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics
{
    /// Contains sampler state, which determines how to sample texture data.
    class sampler_state final
    {
    public:
        static const sampler_state anisotropic_clamp;
        static const sampler_state anisotropic_wrap;
        static const sampler_state linear_clamp;
        static const sampler_state linear_wrap;
        static const sampler_state point_clamp;
        static const sampler_state point_wrap;

    public:
        /// Initializes a new instance of the sampler_state class.
        sampler_state() noexcept;

    private:
        sampler_state(texture_filter filter, texture_address_mode address_mode) noexcept;

    public:
        /// Gets or sets the texture-address mode for the u-coordinate.
        texture_address_mode address_u { texture_address_mode::wrap };

        /// Gets or sets the texture-address mode for the v-coordinate.
        texture_address_mode address_v { texture_address_mode::wrap };

        /// Gets or sets the texture-address mode for the w-coordinate.
        texture_address_mode address_w { texture_address_mode::wrap };

        /// Gets or sets the type of filtering during sampling.
        texture_filter mag_filter { texture_filter::linear };

        /// Gets or sets the type of filtering during sampling.
        texture_filter min_filter { texture_filter::linear };

        /// Gets or sets the maximum anisotropy. The default value is 16.
        std::int32_t max_anisotropy { 16 };

        /// Gets or sets the level of detail (LOD) index of the largest map to use.
        std::size_t max_mip_level { 0 };

        /// Gets or sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
        float mip_map_level_of_detail_bias { 0 };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_SAMPLER_STATE_HPP
