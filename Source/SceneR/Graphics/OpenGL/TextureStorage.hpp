// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP
#define SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "SceneR/IDisposable.hpp"
#include "SceneR/Graphics/OpenGL/TextureTarget.hpp"

namespace SceneR { namespace Graphics {

enum class SurfaceFormat : std::uint32_t;

}}

namespace SceneR { namespace Graphics { namespace OpenGL {

/**
 * Represents an opengl texture object.
 */
class TextureStorage : SceneR::IDisposable
{
private:
    static bool is_compressed_surface_format(SceneR::Graphics::SurfaceFormat format) noexcept;

public:
    /**
     * Initializes a new instance of the TextureStorage class.
     * @param target the texturer target.
     */
    TextureStorage(TextureTarget target) noexcept;

    /**
     * Releases all resources being used by this TextureStorage.
     */
    ~TextureStorage() = default;

public:
    virtual void dispose() override;

public:
    /**
     * Gets the texture object identifier
     */
    std::uint32_t id() const noexcept;

    /**
     * Binds the texture object.
     */
    void bind() const;

    /**
     * Creates the texture object.
     */
    void create();

    /**
     * Unbinds the texture object.
     */
    void unbind() const;

    /**
     * Declares the texture storage parameters.
     * @param levels texture mimap count
     * @param width texture width
     * @param height texture height
     */
    void declare_storage(SceneR::Graphics::SurfaceFormat format
                       , std::size_t                     levels
                       , std::size_t                     width
                       , std::size_t                     height) const;

    /**
     * Adds texture data to the texture object
     * @param format mipmap format
     * @param level mipmap level index
     * @param width mipmap width
     * @param height mipmap height
     * @param data mipmap data
     */
    void set_data(SceneR::Graphics::SurfaceFormat  format
                , std::size_t                      level
                , std::size_t                      width
                , std::size_t                      height
                , const std::vector<std::uint8_t>& data) const;

private:
    std::uint32_t _id;
    TextureTarget _target;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP
