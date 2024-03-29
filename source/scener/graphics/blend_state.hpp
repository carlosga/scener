// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BLEND_STATE_HPP
#define SCENER_GRAPHICS_BLEND_STATE_HPP

#include <cstdint>

#include "scener/graphics/blend_function.hpp"
#include "scener/graphics/blend.hpp"
#include "scener/graphics/color_write_channels.hpp"
#include "scener/math/color.hpp"

namespace scener::graphics
{
    /// Contains blend state for the device.
    class blend_state final
    {
    public:
        static const blend_state additive;
        static const blend_state alpha_blend;
        static const blend_state non_premultiplied;
        static const blend_state opaque;

    public:
        blend_state() = default;

    public:
        /// Gets or sets the arithmetic operation when blending alpha values.
        blend_function alpha_blend_function { blend_function::add };

        /// Gets or sets the blend factor for the destination alpha,
        /// which is the percentage of the destination alpha included in the blended result.
        blend alpha_destination_blend { blend::zero };

        /// Gets or sets the alpha blend factor.
        blend alpha_source_blend { blend::one };

        /// Gets or sets the four-component (RGBA) blend factor for alpha blending.
        math::color blend_factor { math::color::black() };

        /// Gets or sets the arithmetic operation when blending color values.
        blend_function color_blend_function { blend_function::add };

        /// Gets or sets the blend factor for the destination color.
        blend color_destination_blend { blend::zero };

        /// Gets Sets the blend factor for the source color.
        blend color_source_blend { blend::one };

        /// Gets or sets which color channels (RGBA) are enabled for writing during color blending.
        color_write_channels color_write_channels_1 { color_write_channels::all };

        /// Gets or sets which color channels (RGBA) are enabled for writing during color blending.
        color_write_channels color_write_channels_2 { color_write_channels::all };

        /// Gets or sets which color channels (RGBA) are enabled for writing during color blending.
        color_write_channels color_write_channels_3 { color_write_channels::all };

        /// Gets or sets which color channels (RGBA) are enabled for writing during color blending.
        color_write_channels color_write_channels_4 { color_write_channels::all };

        /// Gets or sets a bitmask which defines which samples can be written during multisampling.
        std::uint32_t multi_sample_mask { 0 };

    private:
        blend_state(blend source_blend, blend destination_blend) noexcept;
    };
}

#endif // SCENER_GRAPHICS_BLEND_STATE_HPP
