// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHIC_SDEVICE_HPP
#define SCENER_GRAPHICS_GRAPHIC_SDEVICE_HPP

#include <cstddef>
#include <memory>

#include "scener/graphics/blend_state.hpp"
#include "scener/graphics/depth_stencil_state.hpp"
#include "scener/graphics/presentation_parameters.hpp"
#include "scener/graphics/primitive_type.hpp"
#include "scener/graphics/rasterizer_state.hpp"
#include "scener/graphics/viewport.hpp"
#include "scener/graphics/opengl/display_device.hpp"
#include "scener/math/color.hpp"

namespace scener::graphics
{
    class effect_technique;
    class index_buffer;
    class vertex_buffer;

    /// Performs primitive-based rendering, creates resources, handles system-level variables, adjusts gamma ramp levels,
    /// and creates shaders.
    class graphics_device final
    {
    private:
        static constexpr std::size_t get_element_count(graphics::primitive_type type, std::size_t primitive_count) noexcept
        {
            switch (type)
            {
            case primitive_type::line_list:
                return primitive_count * 2;

            case primitive_type::line_loop:
                return primitive_count;

            case primitive_type::line_strip:
                return primitive_count + 1;

            case primitive_type::point_list:
                return primitive_count;

            case primitive_type::triangle_fan:
                return primitive_count;

            case primitive_type::triangle_list:
                return primitive_count * 3;

            case primitive_type::triangle_strip:
                return primitive_count + 2;
            
            default:
                throw new std::runtime_error("Unknown primitive type");
            }
        }

    public:
        /// Initializes a new instance of the GraphicsDevice class.
        graphics_device() noexcept;

    public:
        opengl::display_device* display_device() const noexcept;

    public:
        /// Clears the resouce buffer
        void clear(const math::color& color) const noexcept;

        /// Renders the specified geometric primitive, based on indexing into an array of vertices.
        /// \param primitive_type   the primitive type.
        /// \param base_vertex      offset to add to each vertex index in the index buffer.
        /// \param min_vertex_index minimum vertex index for vertices used during the call.
        ///                         the minVertexIndex parameter and all of the indices in the
        ///                         index stream are relative to the baseVertex parameter.
        /// \param num_vertices     number of vertices used during the call. The first vertex is located at index:
        /// \                       baseVertex + minVertexIndex.
        /// \param start_index      location in the index array at which to start reading vertices.
        /// \param primitive_count  number of primitives to render. The number of vertices used is a function of
        ///                         primitiveCount and primitiveType.
        void draw_indexed_primitives(primitive_type primitive_type
                                   , std::size_t    base_vertex
                                   , std::size_t    min_vertex_index
                                   , std::size_t    num_vertices
                                   , std::size_t    start_index
                                   , std::size_t    primitive_count) const noexcept;

        /// Renders a sequence of non-indexed geometric primitives of the specified type from the current set of data
        /// input streams.
        /// \param primitive_type  the primitive type.
        /// \param start_vertex    index of the first vertex to load. Beginning at startVertex, the correct number of
        ///                        vertices is read out of the vertex buffer.
        /// \param primitive_count number of primitives to render. The primitiveCount is the number of primitives as
        ///                        determined by the primitive type. If it is a line list, each primitive has two
        ///                        vertices. If it is a triangle list, each primitive has three vertices.
        void draw_primitives(primitive_type primitive_type, std::size_t start_vertex, std::size_t primitive_count) const noexcept;

        /// Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
        /// GraphicsDevice.
        void present() noexcept;

        /// Gets or sets a system-defined instance of a blend state object initialized for alpha blending.
        /// The default value is BlendState.Opaque.
        graphics::blend_state& blend_state() noexcept;

        /// Gets the depth-stencil state.
        graphics::depth_stencil_state& depth_stencil_state() noexcept;

        /// Gets the presentation parameters associated with this graphics device.
        graphics::presentation_parameters& presentation_parameters() noexcept;

        /// Gets rasterizer state.
        graphics::rasterizer_state& rasterizer_state() noexcept;

        /// Gets the viewport identifying the portion of the render target to receive draw calls.
        graphics::viewport& viewport() noexcept;

        /// Sets the viewport identifying the portion of the render target to receive draw calls.
        void viewport(const graphics::viewport& viewport) noexcept;

    public:
        /// Gets or sets the effect used before drawing.
        effect_technique* effect;

        /// Gets or sets the index buffer.
        graphics::index_buffer* index_buffer;

        /// Gets or sets the vertex buffer.
        graphics::vertex_buffer* vertex_buffer;

    private:
        graphics::blend_state                    _blend_state;
        graphics::depth_stencil_state            _depth_stencil_state;
        graphics::presentation_parameters        _presentation_parameters;
        graphics::rasterizer_state               _rasterizer_state;
        graphics::viewport                       _viewport;
        std::unique_ptr<opengl::display_device>  _display_device { nullptr };
    };
}

#endif // SCENER_GRAPHICS_GRAPHIC_SDEVICE_HPP
