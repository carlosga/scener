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

namespace SceneR { namespace Graphics {

class GraphicsDevice;
class GraphicsDeviceManager;

/**
 * Contains blend state for the device.
 */
class BlendState final : public GraphicsResource
{
public:
    /**
     * Initializes a new instance of the BlendState class.
     */
    BlendState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

    /**
     * @brief Copy constructor.
     * @param blendState The blend state to copy from.
     */
    BlendState(const BlendState& blendState) = default;

    /**
     * Releases all resources being used by this BlendState.
     */
    virtual ~BlendState() override = default;

public:
    virtual void dispose() override;

public:
    BlendState& operator=(const BlendState& blendState) = default;

public:
    /**
     * Gets or sets the arithmetic operation when blending alpha values.
     */
    BlendFunction alpha_blend_function { BlendFunction::Add };

    /**
     * Gets or sets the blend factor for the destination alpha,
     * which is the percentage of the destination alpha included in the blended result.
     */
    Blend alpha_destination_blend { Blend::Zero };

    /**
     * Gets or sets the alpha blend factor.
     */
    Blend alpha_source_blend { Blend::One };

    /**
     * Gets or sets the four-component (RGBA) blend factor for alpha blending.
     */
    SceneR::Math::Color blend_factor { SceneR::Math::Color::black };

    /**
     * Gets or sets the arithmetic operation when blending color values.
     */
    BlendFunction color_blend_function { BlendFunction::Add };

    /**
     * Gets or sets the blend factor for the destination color.
     */
    Blend color_destination_blend { Blend::Zero };

    /**
     * Gets Sets the blend factor for the source color.
     */
    Blend color_source_blend { Blend::One };

    /**
     * Gets or sets which color channels (RGBA) are enabled for writing during color blending.
     */
    ColorWriteChannels color_write_channels { ColorWriteChannels::All };

    /**
     * Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
     */
    ColorWriteChannels color_write_channels_1 { ColorWriteChannels::All };

    /**
     * Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
     */
    ColorWriteChannels color_write_channels_2 { ColorWriteChannels::All };

    /**
     * Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
     */
    ColorWriteChannels color_write_channels_3 { ColorWriteChannels::All };

    /**
     * Gets or setsa bitmask which defines which samples can be written during multisampling.
     */
    std::uint32_t multi_sample_mask { 0 };

private:
    void apply() const;

    friend class GraphicsDeviceManager;
};

}}

#endif // SCENER_GRAPHICS_BLENDSTATE_HPP
