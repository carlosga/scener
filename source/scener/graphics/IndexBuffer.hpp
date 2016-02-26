// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_INDEXBUFFER_HPP
#define SCENER_GRAPHICS_INDEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl.h>

#include "scener/graphics/ComponentType.hpp"
#include "scener/graphics/GraphicsResource.hpp"
#include "scener/graphics/opengl/Buffer.hpp"

namespace scener { namespace graphics {

class GraphicsDevice;

/// Describes the rendering order of the vertices in a vertex buffer.
class IndexBuffer final : public GraphicsResource
{
public:
    /// Initializes a new instance of the IndexBuffer class.
    /// \param graphicsDevice the GraphicsDevice object to associate with the index buffer.
    /// \param indexElementType the type of each index.
    /// \param indexCount the number of indices.
    IndexBuffer(gsl::not_null<GraphicsDevice*> graphicsDevice
              , ComponentType                  indexElementType
              , std::size_t                    indexCount) noexcept;

    /// Releases all resources being used by this IndexBuffer.
    ~IndexBuffer() override = default;

public:
    /// Gets the number of indices in the buffer.
    /// \returns the number of indices.
    std::size_t index_count() const noexcept;

    /// Gets the type of each index.
    /// \returns the type of each index.
    ComponentType index_element_type() const noexcept;

    /// Gets the size (in bytes) of each index.
    /// \returns the size (in bytes) of each index.
    std::size_t element_size_in_bytes() const noexcept;

    /// Gets a copy of the index buffer data.
    /// \returns a copy of the index buffer data.
    std::vector<std::uint8_t> get_data() const noexcept;

    /// Gets a copy of the index buffer data, specifying the start index and number of elements.
    /// \param startIndex index of the first element to get.
    /// \param elementCount number of elements to get.
    /// \returns a copy of the index buffer data.
    std::vector<std::uint8_t> get_data(std::size_t startIndex, std::size_t elementCount) const noexcept;

    /// Sets the indices buffer data.
    /// \param data the new indices buffer data.
    void set_data(const gsl::span<const std::uint8_t>& data) const noexcept;

private:
    void bind() const noexcept;
    void unbind() const noexcept;

private:
    scener::graphics::opengl::Buffer _buffer;
    std::size_t                      _indexCount;
    ComponentType                    _indexElementType;

    friend class scener::graphics::GraphicsDevice;
};

}}

#endif // SCENER_GRAPHICS_INDEXBUFFER_HPP
