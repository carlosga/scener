// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP
#define SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP

#include <cstddef>
#include <cstdint>

#include <gsl.h>

#include "SceneR/Graphics/OpenGL/TextureTarget.hpp"

namespace SceneR { namespace Graphics { enum class SurfaceFormat : std::uint32_t; } }

namespace SceneR { namespace Graphics { namespace OpenGL {

/// Represents an opengl texture object.
class TextureStorage final
{
private:
    static bool is_compressed_surface_format(SceneR::Graphics::SurfaceFormat format) noexcept;

public:
    /// Initializes a new instance of the TextureStorage class.
    /// \param target the texturer target.
    TextureStorage(TextureTarget target) noexcept;

    /// Releases all resources being used by this TextureStorage.
    ~TextureStorage() noexcept;

public:
    /// Gets the texture object identifier
    std::uint32_t id() const noexcept;

    /// Binds the texture object.
    void bind() const noexcept;

    /// Unbinds the texture object.
    void unbind() const noexcept;

    /// Declares the texture storage parameters.
    /// \param format the format of the texture data.
    /// \param levels the texture mimap count.
    /// \param width the texture width.
    /// \param height the texture height.
    void declare_storage(SceneR::Graphics::SurfaceFormat format
                       , std::size_t                     levels
                       , std::size_t                     width
                       , std::size_t                     height) const noexcept;

    /// Adds texture data to the texture object.
    /// \param format the format of the mipmap data.
    /// \param level the mipmap level index.
    /// \param width the mipmap width.
    /// \param height the mipmap height.
    /// \param data the mipmap data.
    void set_data(SceneR::Graphics::SurfaceFormat      format
                , std::size_t                          level
                , std::size_t                          width
                , std::size_t                          height
                , const gsl::span<const std::uint8_t>& data) const noexcept;

private:
    void create() noexcept;

private:
    TextureStorage(const TextureStorage&) = delete;
    TextureStorage& operator=(const TextureStorage&) = delete;

private:
    std::uint32_t _id;
    TextureTarget _target;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP
