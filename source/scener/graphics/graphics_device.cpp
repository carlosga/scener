// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "graphics_device.hpp"

#include <gsl/gsl_assert>

#include "scener/graphics/vertex_buffer.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/vertex_declaration.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

namespace scener::graphics
{
    graphics_device::graphics_device(const graphics_adapter&                  adapter
                                   , const graphics::presentation_parameters& presentation_params) noexcept
        : effect                   { nullptr }
        , index_buffer             { nullptr }
        , vertex_buffer            { nullptr }
        , _blend_state             { this }
        , _depth_stencil_state     { this }
        , _presentation_parameters { presentation_params }
        , _rasterizer_state        { this }
        , _viewport                { }
        , _graphics_adapter        { adapter }
        , _adapter                 { }
        , _logical_device          { }
    {
        Expects(_presentation_parameters.device_window_handle != nullptr);

        // Device window handle
        const auto window_handle = _presentation_parameters.device_window_handle;
        // Vulkan instance
        _adapter        = std::make_unique<vulkan::adapter>();
        // Render surface (Vulkan - Wayland based)
        _render_surface = std::make_unique<vulkan::render_surface>(_adapter.get(), window_handle);
        // Physical device
        const auto& gpu = _adapter->get_physical_device(_graphics_adapter.device_id());
        // Logical device (Vulkan)
        _logical_device = gpu.create_logical_device(*_render_surface);
        // Swap chain
        _logical_device->create_swap_chain(*_render_surface);
    }

    void graphics_device::clear(const math::color& color) const noexcept
    {
        std::uint32_t bufferBits = GL_COLOR_BUFFER_BIT;

        glClearColor(color.r, color.g, color.b, color.a);

        if (_depth_stencil_state.depth_buffer_enable)
        {
            bufferBits |= GL_DEPTH_BUFFER_BIT;
            glClearDepth(1.0f);
        }
        if (_depth_stencil_state.stencil_enable)
        {
            bufferBits |= GL_STENCIL_BUFFER_BIT;
            glClearStencil(1);
        }

        glClear(bufferBits);
    }

    void graphics_device::draw_indexed_primitives(primitive_type primitive_type
                                                , std::size_t    base_vertex
                                                , std::size_t    min_vertex_index
                                                , std::size_t    num_vertices
                                                , std::size_t    start_index
                                                , std::size_t    primitive_count) const noexcept
    {
        // Expects(index_buffer  != nullptr);
        // Expects(vertex_buffer != nullptr)
        // Expects(effect        != nullptr)

        auto offset = start_index * index_buffer->element_size_in_bytes();

        effect->begin();
        vertex_buffer->bind();
        index_buffer->bind();

        glDrawElementsBaseVertex(static_cast<GLenum>(primitive_type)
                               , static_cast<GLsizei>(get_element_count(primitive_type, primitive_count))
                               , static_cast<GLenum>(index_buffer->index_element_type())
                               , reinterpret_cast<void*>(offset)
                               , static_cast<GLint>(base_vertex));

        index_buffer->unbind();
        vertex_buffer->unbind();
        effect->end();
    }

    void graphics_device::draw_primitives(primitive_type primitive_type
                                        , std::size_t    start_vertex
                                        , std::size_t    primitive_count) const noexcept
    {
        Expects(vertex_buffer != nullptr);
        Expects(effect        != nullptr);

        effect->begin();
        vertex_buffer->bind();

        glDrawArrays(static_cast<GLenum>(primitive_type)
                   , static_cast<GLint>(start_vertex)
                   , static_cast<GLsizei>(primitive_count));

        vertex_buffer->unbind();
        effect->end();
    }

    void graphics_device::present() noexcept
    {
    }

    blend_state& graphics_device::blend_state() noexcept
    {
        return _blend_state;
    }

    depth_stencil_state& graphics_device::depth_stencil_state() noexcept
    {
        return _depth_stencil_state;
    }

    graphics::presentation_parameters& graphics_device::presentation_parameters() noexcept
    {
        return _presentation_parameters;
    }

    rasterizer_state& graphics_device::rasterizer_state() noexcept
    {
        return _rasterizer_state;
    }

    viewport& graphics_device::viewport() noexcept
    {
        return _viewport;
    }

    void graphics_device::viewport(const graphics::viewport& viewport) noexcept
    {
        _viewport = viewport;
        _viewport.update();
    }
}
