// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE2D_HPP
#define SCENER_GRAPHICS_TEXTURE2D_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

#include <vector>

#include "SceneR/Graphics/SurfaceFormat.hpp"
#include "SceneR/Graphics/Texture.hpp"
#include "SceneR/Graphics/OpenGL/TextureStorage.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

class GraphicsDevice;
class SamplerState;

/**
 * Represents a 2D texture.
 */
class Texture2D final : public Texture
{
public:
    /**
     * Creates a new instance of the Texture2D class.
     *
     * @param graphicsDevice the graphics device
     * @param width the texture width, in pixels
     * @param height the texture height, in pixels
     */
    Texture2D(gsl::not_null<GraphicsDevice*> graphicsDevice, std::size_t width, std::size_t height) noexcept;

    /**
     * Creates a new instance of the Texture2D class.
     *
     * @param graphicsDevice the graphics device
     * @param width the texture width, in pixels
     * @param height the texture height, in pixels
     * @param format texture data format
     */
    Texture2D(gsl::not_null<GraphicsDevice*> graphicsDevice
            , std::size_t                    width
            , std::size_t                    height
            , SurfaceFormat                  format) noexcept;

    /**
     * Releases all resources being used by this texture.
     */
    virtual ~Texture2D() override = default;

public:
    virtual void dispose() override;

public:
    std::uint32_t id() const noexcept override;

    /**
     * Gets the format of the texture data.
     */
    SurfaceFormat format() const noexcept override;

    /**
     * Gets the texture height, in pixels
     */
    std::size_t height() const noexcept;

    /**
     * Gets the number of texture levels in a multilevel texture.
     */
    std::size_t level_count() const noexcept override;

    /**
     * Gets the texture width, in pixels
     */
    std::size_t width() const noexcept;

    /**
     * Gets the texure sampler state.
     * @return the texure sampler state.
     */
    SamplerState* sampler_state() const noexcept;

    /**
     * Sets mipmap data to the texture.
     * @param level the mipmap level.
     * @param data pointer with the mipmap data.
     */
    void set_data(std::size_t level, std::size_t width, std::size_t height, const std::vector<std::uint8_t>& data) const;

    /**
     * Activates the texture object
     */
    void bind() const override;

    /**
     * Deactivates the texture object
     */
    void unbind() const override;

private:
    void declare_storage(std::size_t mipMapLevels);

private:
    SurfaceFormat                 _format;
    std::size_t                   _mipmap_levels;
    std::size_t                   _height;
    std::size_t                   _width;
    std::shared_ptr<SamplerState> _sampler_state;
    OpenGL::TextureStorage        _storage;

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_TEXTURE2D_HPP
