// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_CONSTANTBUFFER_HPP
#define SCENER_GRAPHICS_OPENGL_CONSTANTBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "SceneR/IDisposable.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

class Buffer;

/**
 * Represents an OpenGL Uniform Buffer Object.
 *
 * http://www.opengl.org/wiki/Uniform_Buffer_Object
 */
class ConstantBuffer final : SceneR::IDisposable
{
public:
    /**
     * Initializes a new instance of the ConstantBuffer class.
     * @param name the name of the constant buffer.
     * @param programId the handle of the shader program.
     */
    ConstantBuffer(const std::string& name, const std::uint32_t& programId) noexcept;

    /**
     * Releases all resources being used by this ConstantBuffer.
     */
    virtual ~ConstantBuffer() override = default;

public:
    virtual void dispose() override;

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
    void bind() const;

    /**
     * Creates the constant buffer.
     */
    void create();

    /**
     * Deactivates the constant buffer.
     */
    void unbind() const;

public:
    /**
     * Gets the constant buffer data.
     */
    std::vector<std::uint8_t> get_data() const;

    /**
     * Gets the constant buffer data.
     */
    std::vector<std::uint8_t> get_data(const std::size_t& offset, const std::size_t& count) const;

    /**
     * Sets the constant buffer data.
     */
    void set_data(const void* data) const;

    /**
     * Sets the constant buffer data.
     */
    void set_data(const std::size_t& offset, const std::size_t& count, const void *data) const;

private:
    std::string             _name;
    std::uint32_t           _program_id;
    std::size_t             _index;
    std::int32_t            _binding_point;
    std::size_t             _size;
    std::unique_ptr<Buffer> _buffer_object;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_CONSTANTBUFFER_HPP
