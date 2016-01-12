// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SAMPLERSTATE_HPP
#define SCENER_GRAPHICS_SAMPLERSTATE_HPP

#include <cstddef>
#include <cstdint>

#include "SceneR/Graphics/GraphicsResource.hpp"
#include "SceneR/Graphics/TextureFilter.hpp"
#include "SceneR/Graphics/TextureAddressMode.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

/**
 * Contains sampler state, which determines how to sample texture data.
 */
class SamplerState: public GraphicsResource
{
public:
    /**
     * Initializes a new instance of the SamplerState class.
     */
    SamplerState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

    /**
     * @brief Copy constructor.
     * @param samplerState The sampler state to copy from.
     */
    SamplerState(const SamplerState& samplerState) = default;

    /**
     * Destructor
     */
    virtual ~SamplerState() override = default;

public:
    virtual void dispose() noexcept override;

public:
    SamplerState& operator=(const SamplerState& samplerState) = default;

public:
    /**
     * Gets or sets the texture-address mode for the u-coordinate.
     */
    TextureAddressMode address_u { TextureAddressMode::wrap };

    /**
     * Gets or sets the texture-address mode for the v-coordinate.
     */
    TextureAddressMode address_v { TextureAddressMode::wrap };

    /**
     * Gets or sets the texture-address mode for the w-coordinate.
     */
    TextureAddressMode address_w { TextureAddressMode::wrap };

    /**
     * Gets or sets the type of filtering during sampling.
     */
    TextureFilter mag_filter { TextureFilter::linear };

    /**
     * Gets or sets the type of filtering during sampling.
     */
    TextureFilter min_filter { TextureFilter::linear };

    /**
     * Gets or sets the maximum anisotropy. The default value is 0.
     */
    std::int32_t max_anisotropy { 4 };

    /**
     * Gets or sets the level of detail (LOD) index of the largest map to use.
     */
    std::size_t max_mip_level { 0 };

    /**
     * Gets or sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
     */
    float mip_map_level_of_detail_bias { 0 };

private:
    void apply(std::uint32_t textureId) const noexcept;

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_SAMPLERSTATE_HPP
