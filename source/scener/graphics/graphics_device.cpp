// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "graphics_device.hpp"

#include "scener/graphics/vertex_buffer.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/effect_pass.hpp"
#include "scener/graphics/vulkan/physical_device.hpp"

namespace scener::graphics
{
    graphics_device::graphics_device(const graphics_adapter&                  adapter
                                   , const graphics::presentation_parameters& presentation_params) noexcept
        : _blend_state             { blend_state::opaque }
        , _depth_stencil_state     { depth_stencil_state::default_stencil }
        , _rasterizer_state        { rasterizer_state::cull_counter_clockwise }
        , _presentation_parameters { presentation_params }
        , _viewport                { 0, 0, presentation_params.back_buffer_width, presentation_params.back_buffer_height }
        , _adapter                 { adapter }
        , _render_surface          { }
        , _logical_device          { }
    {
        Expects(_presentation_parameters.device_window_handle != nullptr);

        // Device window handle
        const auto window_handle = _presentation_parameters.device_window_handle;
        // Render surface (Vulkan - Wayland based)
        _render_surface = _adapter.create_render_surface(window_handle);
        // Physical device
        const auto& gpu = _adapter.get_physical_device();
        // Logical device (Vulkan)
        _logical_device = gpu.create_logical_device(*_render_surface, _viewport);
        // Swap chain
        _logical_device->create_swap_chain(*_render_surface);
    }

    void graphics_device::begin_prepare() noexcept
    {
        Expects(_logical_device.get() != nullptr);

        return _logical_device->begin_prepare();
    }

    void graphics_device::end_prepare() noexcept
    {
        Expects(_logical_device.get() != nullptr);

        _logical_device->end_prepare();
    }

    void graphics_device::draw() noexcept
    {
        Expects(_logical_device.get() != nullptr);

        _logical_device->draw(*_render_surface);
    }

    void graphics_device::present() noexcept
    {
        Expects(_logical_device.get() != nullptr);

        _logical_device->present();
    }

    void graphics_device::draw_indexed(std::uint32_t     base_vertex
                                     , std::uint32_t     min_vertex_index
                                     , std::uint32_t     num_vertices
                                     , std::uint32_t     start_index
                                     , std::uint32_t     primitive_count
                                     , vertex_buffer*    vertex_buffer
                                     , index_buffer*     index_buffer
                                     , effect_technique* technique) const noexcept
    {
        Expects(index_buffer  != nullptr);
        Expects(vertex_buffer != nullptr);
        Expects(technique     != nullptr);

        std::for_each(technique->passes().begin(), technique->passes().end(), [&](auto& pass) {
            _logical_device->bind_graphics_pipeline(pass->pipeline());
        });

        _logical_device->draw_indexed(
              base_vertex
            , min_vertex_index
            , num_vertices
            , start_index
            , primitive_count
            , vertex_buffer
            , index_buffer);
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
    }

    vulkan::graphics_pipeline graphics_device::create_graphics_pipeline(const model_mesh_part& model_mesh_part) noexcept
    {
        return _logical_device->create_graphics_pipeline(
            _blend_state
          , _depth_stencil_state
          , _rasterizer_state
          , model_mesh_part);
    }

    vulkan::buffer graphics_device::create_index_buffer(const gsl::span<const std::uint8_t>& data) const noexcept
    {
        return _logical_device->create_index_buffer(data);
    }

    vulkan::buffer graphics_device::create_vertex_buffer(const gsl::span<const std::uint8_t>& data) const noexcept
    {
        return _logical_device->create_vertex_buffer(data);
    }

    vulkan::buffer graphics_device::create_uniform_buffer(std::uint32_t size) const noexcept
    {
        return _logical_device->create_uniform_buffer(size);
    }

    vulkan::texture_object graphics_device::create_texture_object(gsl::not_null<const scener::content::dds::surface*>   texture
                                                                , gsl::not_null<const scener::graphics::sampler_state*> sampler_state
                                                                , vk::ImageTiling                                       tiling
                                                                , vk::ImageUsageFlags                                   usage
                                                                , vk::MemoryPropertyFlags                               required_props) noexcept
    {
        return _logical_device->create_texture_object(texture, sampler_state, tiling, usage, required_props);
    }

    void graphics_device::destroy(const vulkan::texture_object& texture) const noexcept
    {
        _logical_device->destroy(texture);
    }
}
