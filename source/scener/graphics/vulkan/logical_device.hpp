#ifndef SCENER_GRAPHICS_VULKAN_DEVICE_HPP
#define SCENER_GRAPHICS_VULKAN_DEVICE_HPP

#include <cstdint>

#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/memory_allocator.hpp"

namespace scener::graphics::vulkan
{
    class render_surface;

    class logical_device final
    {
    public:
        logical_device(const vk::Device&                 device
                     , std::uint32_t                     graphics_queue_family_index
                     , std::uint32_t                     present_queue_family_index
                     , const vk::SurfaceCapabilitiesKHR& surface_capabilities
                     , const vk::SurfaceFormatKHR&       surface_format
                     , const vk::PresentModeKHR&         present_mode
                     , const vk::FormatProperties&       format_properties) noexcept;

        ~logical_device() noexcept;

    public:
        const vk::Queue& graphics_queue() const noexcept;
        const vk::Queue& present_queue() const noexcept;

        void create_swap_chain(const render_surface& surface) noexcept;

    private:
        void get_device_queues() noexcept;
        void create_sync_primitives() noexcept;
        void create_command_pool() noexcept;
        void create_command_buffer() noexcept;

    private:
        void destroy_sync_primitives() noexcept;
        
    private:
        vk::Device                     _logical_device;
        std::uint32_t                  _graphics_queue_family_index;
        vk::Queue                      _graphics_queue;
        std::uint32_t                  _present_queue_family_index;
        vk::Queue                      _present_queue;
        vk::SurfaceCapabilitiesKHR     _surface_capabilities;
        vk::SurfaceFormatKHR           _surface_format;
        vk::PresentModeKHR             _present_mode;
        vk::FormatProperties           _format_properties;
        vk::CommandPool                _command_pool;
        vk::SwapchainKHR               _swap_chain;
        std::vector<vk::Image>         _swap_chain_images;
        std::vector<vk::CommandBuffer> _command_buffers;
        std::vector<vk::Fence>         _fences;
        std::vector<vk::Semaphore>     _image_acquired_semaphores;
        std::vector<vk::Semaphore>     _draw_complete_semaphores;
        std::vector<vk::Semaphore>     _image_ownership_semaphores;
        std::vector<vk::ImageView>     _image_views;
    };
}

#endif
