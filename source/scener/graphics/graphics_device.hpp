// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHIC_SDEVICE_HPP
#define SCENER_GRAPHICS_GRAPHIC_SDEVICE_HPP

#include <cstddef>
#include <memory>

#include <gsl/gsl>

#include "scener/graphics/blend_state.hpp"
#include "scener/graphics/depth_stencil_state.hpp"
#include "scener/graphics/graphics_adapter.hpp"
#include "scener/graphics/presentation_parameters.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/rasterizer_state.hpp"
#include "scener/graphics/viewport.hpp"
#include "scener/graphics/vulkan/adapter.hpp"
#include "scener/graphics/vulkan/graphics_pipeline.hpp"
#include "scener/graphics/vulkan/logical_device.hpp"
#include "scener/graphics/vulkan/surface.hpp"
#include "scener/graphics/vulkan/texture_object.hpp"
#include "scener/math/color.hpp"

namespace scener::graphics
{
    class effect_technique;
    class effect_pass;
    class vertex_buffer;
    class index_buffer;

    /// Performs primitive-based rendering, creates resources, handles system-level variables, adjusts gamma ramp levels,
    /// and creates shaders.
    class graphics_device final
    {
    public:
        /// Initializes a new instance of the GraphicsDevice class.
        graphics_device(const graphics_adapter&                  adapter
                      , const graphics::presentation_parameters& presentation_params) noexcept;

    public:
        /// Starts the preparation phase
        void begin_prepare() noexcept;

        /// Called by the renderer at the end of drawing; presents the final rendering.
        void end_prepare() noexcept;

        /// Draws the current frame
        void draw() noexcept;

        /// Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
        /// graphics_device.
        void present() noexcept;

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
        void draw_indexed(std::uint32_t     base_vertex
                        , std::uint32_t     min_vertex_index
                        , std::uint32_t     num_vertices
                        , std::uint32_t     start_index
                        , std::uint32_t     primitive_count
                        , vertex_buffer*    vertex_buffer
                        , index_buffer*     index_buffer
                        , effect_technique* technique) const noexcept;

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

        /// Creates a new graphics pipeline.
        vulkan::graphics_pipeline create_graphics_pipeline(const model_mesh_part& model_mesh_part) noexcept;

        /// Creates a new index buffer with the given size.
        /// \para size the buffer size.
        vulkan::buffer create_index_buffer(const gsl::span<const std::uint8_t>& data) const noexcept;

        /// Creates a new vertex buffer with the given size.
        /// \para size the buffer size.
        vulkan::buffer create_vertex_buffer(const gsl::span<const std::uint8_t>& data) const noexcept;

        /// Creates a new vertex buffer with the given size.
        /// \para size the buffer size.
        vulkan::buffer create_uniform_buffer(std::uint32_t size)const noexcept;

        // creates a texture object ( image, view, sampler, ... )
        vulkan::texture_object create_texture_object(gsl::not_null<const scener::content::dds::surface*>   texture
                                                   , gsl::not_null<const scener::graphics::sampler_state*> sampler_state
                                                   , vk::ImageTiling                                       tiling
                                                   , vk::ImageUsageFlags                                   usage
                                                   , vk::MemoryPropertyFlags                               required_props) noexcept;

        /// Destroys the given texture releasing its resources
        void destroy(const vulkan::texture_object& texture) const noexcept;

    private:
        graphics::blend_state                   _blend_state;
        graphics::depth_stencil_state           _depth_stencil_state;
        graphics::rasterizer_state              _rasterizer_state;
        graphics::presentation_parameters       _presentation_parameters;
        graphics::viewport                      _viewport;
        graphics_adapter                        _adapter;
        std::unique_ptr<vulkan::render_surface> _render_surface;
        std::unique_ptr<vulkan::logical_device> _logical_device;
    };
}

#endif // SCENER_GRAPHICS_GRAPHIC_SDEVICE_HPP
