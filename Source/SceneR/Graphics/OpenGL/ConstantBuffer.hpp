// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_CONSTANTBUFFER_HPP
#define SCENER_GRAPHICS_OPENGL_CONSTANTBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

namespace SceneR { namespace Graphics { namespace OpenGL {

class Buffer;

/**
 * Represents an OpenGL Uniform Buffer Object.
 *
 * http://www.opengl.org/wiki/Uniform_Buffer_Object
 */
class ConstantBuffer final
{
public:
    /**
     * Initializes a new instance of the ConstantBuffer class.
     * @param name the name of the constant buffer.
     */
    ConstantBuffer(const std::string& name) noexcept;

    /**
     * Releases all resources being used by this ConstantBuffer.
     */
    ~ConstantBuffer() = default;

public:
    /**
     * Gets the constant buffer binding point.
     */
    std::int32_t binding_point() const noexcept;

    /**
     * Gets the constant buffer block index.
     */
    std::size_t index() const noexcept;

    /**
     * Gets the constant buffer block data size.
     */
    std::size_t size() const noexcept;

public:
    /**
     * Activates the constant buffer.
     */
    void bind() const noexcept;

    /**
     * Creates the constant buffer.
     */
    void create(std::uint32_t programId) noexcept;

    /**
     * Deactivates the constant buffer.
     */
    void unbind() const noexcept;

public:
    /**
     * Gets the constant buffer data.
     */
    std::vector<std::uint8_t> get_data() const noexcept;

    /**
     * Gets the constant buffer data.
     */
    std::vector<std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept;

    /**
     * Sets the constant buffer data.
     */
    void set_data(gsl::not_null<const void*> data) const noexcept;

    /**
     * Sets the constant buffer data.
     */
    void set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept;

private:
    std::size_t             _index;
    std::int32_t            _binding_point;
    std::size_t             _size;
    std::unique_ptr<Buffer> _buffer_object;
    std::string             _name;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_CONSTANTBUFFER_HPP
