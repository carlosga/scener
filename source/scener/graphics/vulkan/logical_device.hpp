// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_DEVICE_HPP
#define SCENER_GRAPHICS_VULKAN_DEVICE_HPP

#include <cstdint>
#include <memory>

#include <gsl/gsl>

#include "scener/graphics/blend_state.hpp"
#include "scener/graphics/depth_stencil_state.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/rasterizer_state.hpp"
#include "scener/graphics/viewport.hpp"
#include "scener/graphics/vulkan/graphics_pipeline.hpp"
#include "scener/graphics/vulkan/image_options.hpp"
#include "scener/graphics/vulkan/image_storage.hpp"
#include "scener/graphics/vulkan/shader.hpp"
#include "scener/graphics/vulkan/vulkan_memory_allocator.hpp"
#include "scener/math/basic_size.hpp"
#include "scener/math/basic_color.hpp"

namespace scener::graphics
{
    class  constant_buffer;
}

namespace scener::graphics::vulkan
{
    class render_surface;

    class logical_device final
    {
    public:
        logical_device(const vk::PhysicalDevice&         physical_device
                     , const vk::Device&                 logical_device
                     , const graphics::viewport&         viewport
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

    public:
        /// Starts the recording of the command buffers
        void begin_prepare() noexcept;

        /// Binds the given graphics pipeline
        void bind_graphics_pipeline(const graphics_pipeline& pipeline) const noexcept;

        /// Renders the specified geometric primitive, based on indexing into an array of vertices.
        void draw_indexed(graphics::primitive_type       primitive_type
                        , std::uint32_t                  base_vertex
                        , std::uint32_t                  min_vertex_index
                        , std::uint32_t                  num_vertices
                        , std::uint32_t                  start_index
                        , std::uint32_t                  primitive_count
                        , const graphics::vertex_buffer* vertex_buffer
                        , const graphics::index_buffer*  index_buffer) noexcept;

        /// Ends the recording of command buffers
        void end_prepare() noexcept;

        // Draws the current frame
        void draw() noexcept;

        /// Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
        /// graphics_device.
        void present() noexcept;

    public:
        buffer create_index_buffer(const gsl::span<const std::uint8_t>& data) noexcept;

        buffer create_vertex_buffer(const gsl::span<const std::uint8_t>& data) noexcept;

        buffer create_uniform_buffer(std::uint64_t count) noexcept;

        buffer create_buffer(buffer_usage                         usage
                           , vk::SharingMode                      sharing_mode
                           , const gsl::span<const std::uint8_t>& data) noexcept;

    public:
        void create_swap_chain(const render_surface& surface) noexcept;
        void recreate_swap_chain(const render_surface& surface) noexcept;

    public:
        graphics_pipeline create_graphics_pipeline(
              const graphics::blend_state&         color_blend_state
            , const graphics::depth_stencil_state& depth_stencil_state
            , const graphics::rasterizer_state&    rasterization_state
            , const graphics::model_mesh_part&     model_mesh_part) const noexcept;

        void create_descriptor_sets(const graphics::constant_buffer& constant_buffer) noexcept;

    public:
        image_storage create_image(const image_options& options) noexcept;
        vk::Sampler create_sampler(const gsl::not_null<sampler_state*> sampler) const noexcept;

    private:
        void create_viewport(const graphics::viewport& viewport);
        void create_allocator(const vk::PhysicalDevice& physical_device, const vk::Device& logical_device) noexcept;
        void get_device_queues() noexcept;
        void begin_single_time_commands() noexcept;
        void end_single_time_commands() noexcept;
        void reset_fence(const vk::Fence& fence) const noexcept;
        void create_sync_primitives() noexcept;
        void create_command_pools() noexcept;
        void create_command_buffers() noexcept;
        void create_image_views() noexcept;
        void create_descriptor_layout() noexcept;
        void create_render_pass() noexcept;
        void create_depth_buffer(vk::Extent2D extent) noexcept;
        void create_frame_buffers(vk::Extent2D extent) noexcept;
        void create_pipeline_cache() noexcept;
        void create_descriptor_pool() noexcept;
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
        vk::Viewport                     _viewport;
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
        std::uint32_t                    _frame_index;
        vk::Format                       _depth_format;
        image_storage                    _depth_buffer;
        vk::PipelineCache                _pipeline_cache;
        vk::DescriptorPool               _descriptor_pool;
        vk::DescriptorSetLayout          _descriptor_set_layout;
        vk::PipelineLayout               _pipeline_layout;
        VmaAllocator                     _allocator;
    };
}

#endif
