// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_DEVICE_HPP
#define SCENER_GRAPHICS_VULKAN_DEVICE_HPP

#include <cstdint>

#include <vulkan/vulkan.hpp>
#include <scener/math/basic_size.hpp>
#include <scener/math/basic_color.hpp>

#include "scener/graphics/vulkan/image.hpp"
#include "scener/graphics/vulkan/image_options.hpp"
#include "scener/graphics/vulkan/memory_allocator.hpp"

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

        const memory_allocator& allocator() const noexcept;

        const scener::math::basic_color<float>& clear_color() const noexcept;
        void clear_color(const scener::math::basic_color<float>& color) noexcept;

        void create_swap_chain(const render_surface& surface) noexcept;
        void create_render_targets(const scener::math::basic_size<std::uint32_t>& size) noexcept;
        void record_command_buffers() const noexcept;

    public:
        image create_image(const image_options& options) const noexcept;
        void create_sampler() const noexcept;

    private:
        void get_device_queues() noexcept;
        void create_sync_primitives() noexcept;
        void destroy_sync_primitives() noexcept;
        void create_command_pool() noexcept;
        void create_command_buffers() noexcept;
        void create_frame_buffers() noexcept;
        void create_render_pass() noexcept;

    private:
        vk::Device                       _logical_device;
        memory_allocator                 _allocator;
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
