// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODELMESHPART_HPP
#define SCENER_GRAPHICS_MODELMESHPART_HPP

#include <cstddef>
#include <memory>
#include <string>

#include "scener/graphics/PrimitiveType.hpp"

namespace scener { namespace content { namespace readers { template <typename T> class ContentTypeReader; } } }

namespace scener { namespace graphics {

class effect_technique;
class index_buffer;
class vertex_buffer;

/// Represents a batch of geometry information to submit to the graphics device during rendering.
/// Each ModelMeshPart is a subdivision of a ModelMesh object. The ModelMesh class is split into
/// multiple ModelMeshPart objects, typically based on material information.
class model_mesh_part final
{
public:
    /// Initializes a new instance of the ModelMeshPart class.
    model_mesh_part() = default;

public:
    /// Gets the index buffer for this mesh part.
    /// \returns the index buffer.
    graphics::index_buffer* index_buffer() const noexcept;

    /// Gets the vertex buffer for this mesh part.
    /// \returns the vertex buffer
    graphics::vertex_buffer* vertex_buffer() const noexcept;

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
    graphics::primitive_type primitive_type() const noexcept;

public:
    /// Gets or sets the effect for this mesh part.
    std::shared_ptr<effect_technique> effect = { nullptr };

private:
    std::unique_ptr<graphics::index_buffer>  _index_buffer       = { nullptr };
    std::unique_ptr<graphics::vertex_buffer> _vertex_buffer      = { nullptr };
    std::size_t                              _start_index        = { 0 };
    std::size_t                              _vertex_offset      = { 0 };
    std::size_t                              _vertex_count       = { 0 };
    std::size_t                              _primitive_count    = { 0 };
    graphics::primitive_type                 _primitive_type     = { primitive_type::triangle_list };

    template <typename T> friend class scener::content::readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_MODELMESHPART_HPP
