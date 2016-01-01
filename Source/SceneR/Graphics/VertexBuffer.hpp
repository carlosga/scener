// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXBUFFER_HPP
#define SCENER_GRAPHICS_VERTEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "SceneR/Graphics/GraphicsResource.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

class Buffer;
class VertexArrayObject;

}}}

namespace SceneR { namespace Graphics {

class GraphicsDevice;
class VertexDeclaration;

/**
 * Represents a list of 3D vertices to be streamed to the graphics device.
 */
class VertexBuffer final : public GraphicsResource
{
public:
    /**
     * Initializes a new instance of the VertexBuffer class.
     * @param graphicsDevice the graphics device.
     */
    VertexBuffer(gsl::not_null<GraphicsDevice*>     graphicsDevice
               , std::size_t                        vertexCount
               , std::unique_ptr<VertexDeclaration> vertexDeclaration) noexcept;

    /**
     * Releases all resources being used by the current VertexBuffer
     */
    virtual ~VertexBuffer() override = default;

public:
    virtual void dispose() override;

public:
    /**
     * Gets the number of vertex for the current buffer
     */
    std::size_t vertex_count() const noexcept;

    /**
     * Gets the vertex buffer data
     */
    std::vector<std::uint8_t> get_data() const noexcept;

    /**
     * Gets the vertex buffer data
     */
    std::vector<std::uint8_t> get_data(std::size_t startIndex, std::size_t elementCount) const noexcept;

    /**
     * Sets the vertex buffer data
     */
    void set_data(const gsl::span<std::uint8_t>& data) const noexcept;

    /**
     * Defines per-vertex data in a buffer.
     */
    VertexDeclaration* vertex_declaration() const noexcept;

private:
    void bind() noexcept;
    void unbind() noexcept;
    void create() noexcept;

private:
    std::uint32_t                                                _binding_index;
    std::size_t                                                  _vertex_count;
    std::unique_ptr<VertexDeclaration>                           _vertex_declaration;
    std::unique_ptr<SceneR::Graphics::OpenGL::VertexArrayObject> _vao;
    std::unique_ptr<SceneR::Graphics::OpenGL::Buffer>            _vbo;

    friend class SceneR::Graphics::GraphicsDevice;
};

}}

#endif // SCENER_GRAPHICS_VERTEXBUFFER_HPP
