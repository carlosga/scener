// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODELMESHPART_HPP
#define SCENER_GRAPHICS_MODELMESHPART_HPP

#include <cstddef>
#include <memory>
#include <string>

#include "SceneR/Graphics/PrimitiveType.hpp"

namespace scener { namespace content { namespace readers { template <typename T> class ContentTypeReader; } } }

namespace scener { namespace graphics {

class EffectTechnique;
class IndexBuffer;
class VertexBuffer;

/// Represents a batch of geometry information to submit to the graphics device during rendering.
/// Each ModelMeshPart is a subdivision of a ModelMesh object. The ModelMesh class is split into
/// multiple ModelMeshPart objects, typically based on material information.
class ModelMeshPart final
{
public:
    /// Initializes a new instance of the ModelMeshPart class.
    ModelMeshPart() = default;

public:
    /// Gets the index buffer for this mesh part.
    /// \returns the index buffer.
    IndexBuffer* index_buffer() const noexcept;

    /// Gets the vertex buffer for this mesh part.
    /// \returns the vertex buffer
    VertexBuffer* vertex_buffer() const noexcept;

    /// Gets the location in the index array at which to start reading vertices.
    /// \returns location in the index array at which to start reading vertices.
    std::size_t start_index() const noexcept;

    /// Gets the offset (in vertices) from the top of vertex buffer.
    /// \returns the offset (in vertices) from the top of vertex buffer.
    std::size_t vertex_offset() const noexcept;

    /// Gets the number of vertices used during a draw call.
    /// \returns the number of vertices used during a draw call.
    std::size_t vertex_count() const noexcept;

    /// Gets the number of primitives to render.
    /// \returns the number of primitives to render. The number of vertices used is a function of primitiveCount and
    ///          primitiveType.
    std::size_t primitive_count() const noexcept;

    /// Gets the type of primitives to render.
    /// \returns the type of primitives to render.
    PrimitiveType primitive_type() const noexcept;

public:
    /// Gets or sets the effect for this mesh part.
    std::shared_ptr<EffectTechnique> effect = { nullptr };

private:
    std::unique_ptr<IndexBuffer>    _index_buffer       = { nullptr };
    std::unique_ptr<VertexBuffer>   _vertex_buffer      = { nullptr };
    std::size_t                     _start_index        = { 0 };
    std::size_t                     _vertex_offset      = { 0 };
    std::size_t                     _vertex_count       = { 0 };
    std::size_t                     _primitive_count    = { 0 };
    scener::graphics::PrimitiveType _primitive_type     = { PrimitiveType::triangle_list };

    template <typename T> friend class scener::content::readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_MODELMESHPART_HPP
