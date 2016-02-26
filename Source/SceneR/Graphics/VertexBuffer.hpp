// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXBUFFER_HPP
#define SCENER_GRAPHICS_VERTEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "SceneR/Graphics/GraphicsResource.hpp"
#include "SceneR/Graphics/VertexDeclaration.hpp"
#include "SceneR/Graphics/OpenGL/Buffer.hpp"
#include "SceneR/Graphics/OpenGL/VertexArrayObject.hpp"

namespace scener { namespace graphics {

class GraphicsDevice;

/// Represents a list of 3D vertices to be streamed to the graphics device.
class VertexBuffer final : public GraphicsResource
{
public:
    /// Initializes a new instance of the VertexBuffer class.
    /// \param graphicsDevice the GraphicsDevice associated with this VertexBuffer.
    /// \param vertexCount the number of vertices.
    /// \param vertexDeclaration the vertex declaration, which describes per-vertex data.
    VertexBuffer(gsl::not_null<GraphicsDevice*> graphicsDevice
               , std::size_t                    vertexCount
               , const VertexDeclaration&       vertexDeclaration) noexcept;

    /// Releases all resources being used by the current VertexBuffer
    ~VertexBuffer() override = default;

public:
    /// Gets the number of vertex for the current buffer.
    std::size_t vertex_count() const noexcept;

    /// Returns a copy of the vertex buffer data.
    std::vector<std::uint8_t> get_data() const noexcept;

    /// Gets a copy of the vertex buffer data, specifying the start index and number of elements.
    /// \param startIndex index of the first element to get.
    /// \param elementCount number of elements to get.
    std::vector<std::uint8_t> get_data(std::size_t startIndex, std::size_t elementCount) const noexcept;

    /// Sets the vertex buffer data.
    /// \param data the new vertex buffer data.
    void set_data(const gsl::span<const std::uint8_t>& data) const noexcept;

    /// Defines per-vertex data in a buffer.
    /// \returns the per vertex data definition of this VertexBuffer.
    const VertexDeclaration& vertex_declaration() const noexcept;

private:
    void bind() noexcept;
    void unbind() noexcept;

private:
    std::uint32_t                               _binding_index;
    std::size_t                                 _vertex_count;
    VertexDeclaration                           _vertex_declaration;
    scener::graphics::opengl::VertexArrayObject _vao;
    scener::graphics::opengl::Buffer            _vbo;

    friend class scener::graphics::GraphicsDevice;
};

}}

#endif // SCENER_GRAPHICS_VERTEXBUFFER_HPP
