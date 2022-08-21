// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODEL_MESH_PART_HPP
#define SCENER_GRAPHICS_MODEL_MESH_PART_HPP

#include <cstddef>
#include <memory>
#include <string>

#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/primitive_type.hpp"
#include "scener/graphics/vertex_buffer.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics
{
    /// Represents a batch of geometry information to submit to the graphics device during rendering.
    /// Each ModelMeshPart is a subdivision of a ModelMesh object. The ModelMesh class is split into
    /// multiple ModelMeshPart objects, typically based on material information.
    class model_mesh_part final
    {
    public:
        /// Gets the index buffer for this mesh part.
        /// \returns the index buffer.
        graphics::index_buffer* index_buffer() const noexcept;

        /// Gets the vertex buffer for this mesh part.
        /// \returns the vertex buffer
        graphics::vertex_buffer* vertex_buffer() const noexcept;

        /// Gets the effect technique for this mesh part.
        /// \returns the effect technique
        graphics::effect_technique* effect_technique() const noexcept;

        /// Gets the location in the index array at which to start reading vertices.
        /// \returns location in the index array at which to start reading vertices.
        std::uint32_t start_index() const noexcept;

        /// Gets the offset (in vertices) from the top of vertex buffer.
        /// \returns the offset (in vertices) from the top of vertex buffer.
        std::uint32_t vertex_offset() const noexcept;

        /// Gets the number of vertices used during a draw call.
        /// \returns the number of vertices used during a draw call.
        std::uint32_t vertex_count() const noexcept;

        /// Gets the number of primitives to render.
        /// \returns the number of primitives to render. The number of vertices used is a function of primitiveCount and
        ///          primitiveType.
        std::uint32_t primitive_count() const noexcept;

        /// Gets the type of primitives to render.
        /// \returns the type of primitives to render.
        graphics::primitive_type primitive_type() const noexcept;

    private:
        std::unique_ptr<graphics::index_buffer>     _index_buffer    = { nullptr };
        std::unique_ptr<graphics::vertex_buffer>    _vertex_buffer   = { nullptr };
        std::shared_ptr<graphics::effect_technique> _effect          = { nullptr };
        std::uint32_t                               _start_index     = { 0 };
        std::uint32_t                               _vertex_offset   = { 0 };
        std::uint32_t                               _vertex_count    = { 0 };
        std::uint32_t                               _primitive_count = { 0 };
        graphics::primitive_type                    _primitive_type  = { primitive_type::triangle_list };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_MODEL_MESH_PART_HPP
