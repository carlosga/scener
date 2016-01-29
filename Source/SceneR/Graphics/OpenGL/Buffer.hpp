// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFER_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl.h>

namespace SceneR { namespace Graphics { namespace OpenGL {

enum class BufferTarget : std::uint32_t;
enum class BufferUsage  : std::uint32_t;

/**
 * Represents an OpenGL buffer object.
 */
class Buffer final
{
public:
    /**
     * Initializes a new instance of the Buffer class.
     * @param target the buffer target.
     * @param usage the buffer usage.
     */
    Buffer(BufferTarget target, BufferUsage usage) noexcept;

    /**
     * Releases all resources being used by this Buffer.
     */
    ~Buffer() noexcept;

public:
    /**
     * Gets the buffer object identifier.
     */
    std::uint32_t id() const noexcept;

    /**
     * Gets the buffer object target.
     */
    BufferTarget target() const noexcept;

    /**
     * Gets the buffer object usage.
     */
    BufferUsage usage() const noexcept;

    /**
     * Activates the buffer object.
     */
    void bind() const noexcept;

    /**
     * Deactivates the buffer object.
     */
    void unbind() const noexcept;

    /**
     * Gets a subset of data from a buffer object's data store.
     * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
     * @param size specifies the size in bytes of the data store region being replaced.
     */
    std::vector<std::uint8_t> get_data(std::size_t offset, std::size_t size) const noexcept;

    /**
     * Creates and initializes the buffer object data store.
     * @param size specifies the size in bytes of the buffer object's new data store.
     * @param data specifies a pointer to data that will be copied into the data store for initialization,
     *             or NULL if no data is to be copied.
     */
    void set_data(std::size_t size, gsl::not_null<const void*> data) const noexcept;

    /**
     * Updates a subset of a buffer object's data store
     * @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
     * @param size specifies the size in bytes of the data store region being replaced.
     * @param data specifies a pointer to the new data that will be copied into the data store.
     */
    void set_data(std::size_t offset, std::size_t size, gsl::not_null<const void*> data) const noexcept;

    /**
     * Invalidate the content of a buffer object's data store
     */
    void invalidate() const noexcept;

    /**
     *  Invalidate a region of a buffer object's data store
     *  @param offset the offset within the buffer's data store of the start of the range to be invalidated.
     *  @param length the length of the range within the buffer's data store to be invalidated.
     */
    void invalidate(std::size_t offset, std::size_t length) const noexcept;

private:
    void create() noexcept;

private:
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

private:
    std::uint32_t _id;
    BufferTarget  _target;
    BufferUsage   _usage;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_BUFFER_HPP
