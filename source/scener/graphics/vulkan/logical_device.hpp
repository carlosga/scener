// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_DEVICE_HPP
#define SCENER_GRAPHICS_VULKAN_DEVICE_HPP

#include <cstdint>
#include <memory>

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/blend_state.hpp"
#include "scener/graphics/depth_stencil_state.hpp"
#include "scener/graphics/primitive_type.hpp"
#include "scener/graphics/rasterizer_state.hpp"
#include "scener/graphics/viewport.hpp"
#include "scener/graphics/vulkan/resource_deleter.hpp"
#include "scener/graphics/vulkan/image_options.hpp"
#include "scener/graphics/vulkan/shader.hpp"
#include "scener/math/basic_size.hpp"
#include "scener/math/basic_color.hpp"

struct VmaAllocator_T;

namespace scener::graphics
{
    class graphics_pipeline;
    class index_buffer;
    class vertex_buffer;
}

namespace scener::graphics::vulkan
{
    class render_surface;

    class logical_device final
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
                throw std::runtime_error("Unknown primitive type");
            }
        }

    public:
        logical_device(const vk::PhysicalDevice&         physical_device
                     , const vk::Device&                 logical_device
                     , std::uint32_t                     graphics_queue_family_index
                     , std::uint32_t                     present_queue_family_index
                     , const vk::SurfaceCapabilitiesKHR& surface_capabilities
                     , const vk::SurfaceFormatKHR&       surface_format
                     , const vk::Format&                 depth_format
                     , const vk::PresentModeKHR&         present_mode
                     , const vk::FormatProperties&       format_properties) noexcept;

        ~logical_device() noexcept;

    public:
        const vk::Queue& graphics_queue() const noexcept;
        const vk::Queue& present_queue() const noexcept;
        const scener::math::basic_color<float>& clear_color() const noexcept;
        void clear_color(const scener::math::basic_color<float>& color) noexcept;

    public:
        /// Starts the drawing of a frame
        bool begin_draw([[maybe_unused]] const render_surface& surface) noexcept;

        void bind_graphics_pipeline(const graphics::graphics_pipeline* pipeline) noexcept;

        /// Renders the specified geometric primitive, based on indexing into an array of vertices.
        void draw_indexed(graphics::primitive_type       primitive_type
                        , std::size_t                    base_vertex
                        , std::size_t                    min_vertex_index
                        , std::size_t                    num_vertices
                        , std::size_t                    start_index
                        , std::size_t                    primitive_count
                        , const graphics::vertex_buffer* vertex_buffer
                        , const graphics::index_buffer*  index_buffer) noexcept;

        /// Called by the renderer at the end of drawing; presents the final rendering.
        void end_draw([[maybe_unused]] const render_surface& surface) noexcept;

        /// Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
        /// graphics_device.
        void present([[maybe_unused]] const render_surface& surface) noexcept;

    public:
        std::unique_ptr<buffer, buffer_deleter>
        create_vertex_buffer(const gsl::span<const std::uint8_t>& data) noexcept;

        std::unique_ptr<buffer, buffer_deleter>
        create_index_buffer(const gsl::span<const std::uint8_t>& data) noexcept;

        std::unique_ptr<buffer, buffer_deleter>
        create_buffer(
              buffer_usage                         usage
            , vk::SharingMode                      sharing_mode
            , const gsl::span<const std::uint8_t>& data) noexcept;

    public:
        void create_swap_chain(const render_surface& surface) noexcept;
        void recreate_swap_chain(const render_surface& surface) noexcept;
        vk::UniquePipeline create_graphics_pipeline(
              const graphics::viewport&                           viewport_state
            , const graphics::blend_state&                        color_blend_state
            , const graphics::depth_stencil_state&                depth_stencil_state
            , const graphics::rasterizer_state&                   rasterization_state
            , const std::vector<std::shared_ptr<vulkan::shader>>& shaders) noexcept;

    public:
        std::unique_ptr<image_storage, image_deleter>
        create_image(const image_options& options) const noexcept;

        vk::Sampler create_sampler(const gsl::not_null<sampler_state*> sampler) const noexcept;

    private:
        void create_allocator(const vk::PhysicalDevice& physical_device, const vk::Device& logical_device) noexcept;
        void get_device_queues() noexcept;
        void begin_single_time_commands() noexcept;
        void end_single_time_commands() noexcept;
        void reset_fence(const vk::Fence& fence) const noexcept;
        void create_sync_primitives() noexcept;
        void create_command_pools() noexcept;
        void create_command_buffers() noexcept;
        void create_render_pass() noexcept;
        void create_depth_buffer(vk::Extent2D extent) noexcept;
        void create_frame_buffers(vk::Extent2D extent) noexcept;
        void record_command_buffers() const noexcept;
        void destroy_sync_primitives() noexcept;
        void destroy_command_buffers() noexcept;
        void destroy_command_pools() noexcept;
        void destroy_swapchain_views() noexcept;
        void destroy_frame_buffers() noexcept;
        void destroy_swap_chain() noexcept;

    private:
        vk::PipelineColorBlendStateCreateInfo vk_color_blend_state(
            const graphics::blend_state&           state
          , vk::PipelineColorBlendAttachmentState& attachment) const noexcept;
        vk::PipelineDepthStencilStateCreateInfo vk_depth_stencil_state(const graphics::depth_stencil_state& state) const noexcept;
        vk::PipelineRasterizationStateCreateInfo vk_rasterizer_state(const graphics::rasterizer_state& state) const noexcept;

    private:
        vk::Device                       _logical_device;
        VmaAllocator_T*                  _allocator;
        std::uint32_t                    _graphics_queue_family_index;
        vk::Queue                        _graphics_queue;
        std::uint32_t                    _present_queue_family_index;
        vk::Queue                        _present_queue;
        vk::SurfaceCapabilitiesKHR       _surface_capabilities;
        vk::SurfaceFormatKHR             _surface_format;
        vk::PresentModeKHR               _present_mode;
        vk::FormatProperties             _format_properties;
        vk::CommandPool                  _command_pool;
        vk::CommandPool                  _single_time_command_pool;
        vk::SwapchainKHR                 _swap_chain;
        vk::RenderPass                   _render_pass;
        std::vector<vk::Image>           _swap_chain_images;
        std::vector<vk::ImageView>       _swap_chain_image_views;
        std::vector<vk::Framebuffer>     _frame_buffers;
        std::vector<vk::CommandBuffer>   _command_buffers;
        vk::CommandBuffer                _single_time_command_buffer;
        std::vector<vk::Fence>           _fences;
        vk::Fence                        _single_time_command_fence;
        std::vector<vk::Semaphore>       _image_acquired_semaphores;
        std::vector<vk::Semaphore>       _draw_complete_semaphores;
        std::vector<vk::Semaphore>       _image_ownership_semaphores;
        scener::math::basic_color<float> _clear_color;
        std::uint64_t                    _next_command_buffer_index;
        std::uint32_t                    _acquired_image_index;

        vk::Format                                    _depth_format;
        std::unique_ptr<image_storage, image_deleter> _depth_buffer;
    };
}

#endif
