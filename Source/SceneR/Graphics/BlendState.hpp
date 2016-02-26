// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BLENDSTATE_HPP
#define SCENER_GRAPHICS_BLENDSTATE_HPP

#include <cstdint>

#include <gsl.h>

#include "SceneR/Graphics/GraphicsResource.hpp"
#include "SceneR/Graphics/BlendFunction.hpp"
#include "SceneR/Graphics/Blend.hpp"
#include "SceneR/Graphics/ColorWriteChannels.hpp"
#include "SceneR/Math/Color.hpp"

namespace scener { namespace graphics {

class GraphicsDevice;
class GraphicsDeviceManager;

/// Contains blend state for the device.
class BlendState final : public GraphicsResource
{
public:
    /// Initializes a new instance of the BlendState class.
    /// \param graphicsDevice the GraphicsDevice associated with this BlendState.
    BlendState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

    /// Releases all resources being used by this BlendState.
    ~BlendState() override = default;

public:
    /// Gets or sets the arithmetic operation when blending alpha values.
    BlendFunction alpha_blend_function { BlendFunction::add };

    /// Gets or sets the blend factor for the destination alpha,
    /// which is the percentage of the destination alpha included in the blended result.
    Blend alpha_destination_blend { Blend::zero };

    /// Gets or sets the alpha blend factor.
    Blend alpha_source_blend { Blend::one };

    /// Gets or sets the four-component (RGBA) blend factor for alpha blending.
    scener::math::Color blend_factor { scener::math::Color::black };

    /// Gets or sets the arithmetic operation when blending color values.
    BlendFunction color_blend_function { BlendFunction::add };

    /// Gets or sets the blend factor for the destination color.
    Blend color_destination_blend { Blend::zero };

    /// Gets Sets the blend factor for the source color.
    Blend color_source_blend { Blend::one };

    /// Gets or sets which color channels (RGBA) are enabled for writing during color blending.
    ColorWriteChannels color_write_channels { ColorWriteChannels::all };

    /// Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
    ColorWriteChannels color_write_channels_1 { ColorWriteChannels::all };

    /// Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
    ColorWriteChannels color_write_channels_2 { ColorWriteChannels::all };

    /// Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
    ColorWriteChannels color_write_channels_3 { ColorWriteChannels::all };

    /// Gets or setsa bitmask which defines which samples can be written during multisampling.
    std::uint32_t multi_sample_mask { 0 };

private:
    void apply() const noexcept;

    friend class GraphicsDeviceManager;
};

}}

#endif // SCENER_GRAPHICS_BLENDSTATE_HPP
