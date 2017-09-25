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
#include "scener/graphics/rasterizer_state.hpp"
#include "scener/graphics/viewport.hpp"
#include "scener/graphics/vulkan/buffer.hpp"
#include "scener/graphics/vulkan/image.hpp"
#include "scener/graphics/vulkan/image_options.hpp"
#include "scener/graphics/vulkan/shader.hpp"
#include "scener/math/basic_size.hpp"
#include "scener/math/basic_color.hpp"

struct VmaAllocator_T;

namespace scener::graphics::vulkan
{
    class render_surface;

    class logical_device final
    {
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
        std::unique_ptr<buffer, buffer_deleter> create_vertex_buffer(std::uint32_t size) noexcept;
        std::unique_ptr<buffer, buffer_deleter> create_index_buffer(std::uint32_t size) noexcept;
        std::unique_ptr<buffer, buffer_deleter> create_buffer(buffer_usage usage, std::uint32_t size) noexcept;

    public:
        void create_swap_chain(const render_surface& surface) noexcept;
        vk::UniquePipeline create_graphics_pipeline(
              const graphics::viewport&                           viewport_state
            , const graphics::blend_state&                        color_blend_state
            , const graphics::depth_stencil_state&                depth_stencil_state
            , const graphics::rasterizer_state&                   rasterization_state
            , const std::vector<std::shared_ptr<vulkan::shader>>& shaders) noexcept;

    public:
        image create_image(const image_options& options) const noexcept;
        vk::Sampler create_sampler(const gsl::not_null<sampler_state*> sampler) const noexcept;

    private:
        void create_allocator(const vk::PhysicalDevice& physical_device, const vk::Device& logical_device) noexcept;
        void get_device_queues() noexcept;
        void create_sync_primitives() noexcept;
        void destroy_sync_primitives() noexcept;
        void create_command_pool() noexcept;
        void create_command_buffers() noexcept;
        void create_render_pass() noexcept;
        void create_frame_buffers(vk::Extent2D extent) noexcept;
        void record_command_buffers() const noexcept;
        void destroy_command_buffers() noexcept;
        void destroy_swapchain_views() noexcept;
        void destroy_frame_buffers() noexcept;

    private:
        vk::PipelineColorBlendStateCreateInfo vk_color_blend_state(
            const graphics::blend_state&           state
          , vk::PipelineColorBlendAttachmentState& attachment) const noexcept;
        vk::PipelineDepthStencilStateCreateInfo vk_depth_stencil_state(const graphics::depth_stencil_state& state) const noexcept;
        vk::PipelineRasterizationStateCreateInfo vk_rasterizer_state(const graphics::rasterizer_state& state) const noexcept;

    private:
        vk::Device                       _logical_device;
        std::unique_ptr<VmaAllocator_T>  _allocator;
        std::uint32_t                    _graphics_queue_family_index;
        vk::Queue                        _graphics_queue;
        std::uint32_t                    _present_queue_family_index;
        vk::Queue                        _present_queue;
        vk::SurfaceCapabilitiesKHR       _surface_capabilities;
        vk::SurfaceFormatKHR             _surface_format;
        vk::Format                       _depth_format;
        vk::PresentModeKHR               _present_mode;
        vk::FormatProperties             _format_properties;
        vk::CommandPool                  _command_pool;
        vk::SwapchainKHR                 _swap_chain;
        vk::RenderPass                   _render_pass;
        std::vector<vk::Image>           _swap_chain_images;
        std::vector<vk::ImageView>       _swap_chain_image_views;
        std::vector<vk::Framebuffer>     _frame_buffers;
        std::vector<vk::CommandBuffer>   _command_buffers;
        std::vector<vk::Fence>           _fences;
        std::vector<vk::Semaphore>       _image_acquired_semaphores;
        std::vector<vk::Semaphore>       _draw_complete_semaphores;
        std::vector<vk::Semaphore>       _image_ownership_semaphores;
        scener::math::basic_color<float> _clear_color;
    };
}

#endif
