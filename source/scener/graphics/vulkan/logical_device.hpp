#ifndef SCENER_GRAPHICS_VULKAN_DEVICE_HPP
#define SCENER_GRAPHICS_VULKAN_DEVICE_HPP

#include <vulkan/vulkan.hpp>
#include <cstdint>
#include <memory>
#include <vector>

#include <gsl/gsl>

namespace scener::graphics::vulkan
{
    class display_surface;

    class logical_device final
    {
        inline const static std::uint32_t s_buffer_count = 2;

    public:
        logical_device(const vk::Device&                 device
                     , std::uint32_t                     graphics_queue_family_index
                     , const vk::Queue&                  graphics_queue
                     , std::uint32_t                     present_queue_family_index
                     , const vk::Queue&                  present_queue
                     , const vk::SurfaceCapabilitiesKHR& surface_capabilities
                     , const vk::SurfaceFormatKHR&       surface_format
                     , const vk::PresentModeKHR&         present_mode) noexcept;

        ~logical_device() noexcept;

    public:
        const vk::Queue& graphics_queue() const noexcept;
        const vk::Queue& present_queue() const noexcept;

        void create_swap_chain(gsl::not_null<const display_surface*> surface) noexcept;

    private:
        void create_sync_primitives() noexcept;
        void create_command_pool() noexcept;
        void create_command_buffer() noexcept;

    private:
        void destroy_sync_primitives() noexcept;
        
    private:
        std::unique_ptr<vk::Device> _logical_device;
        std::uint32_t               _graphics_queue_family_index;
        vk::Queue                   _graphics_queue;
        std::uint32_t               _present_queue_family_index;
        vk::Queue                   _present_queue;
        vk::SurfaceCapabilitiesKHR  _surface_capabilities;
        vk::SurfaceFormatKHR        _surface_format;
        vk::PresentModeKHR          _present_mode;
        vk::Fence                   _fences[s_buffer_count];
        vk::CommandPool             _command_pool;
        vk::CommandBuffer           _command_buffer;
        vk::Semaphore               _image_acquired_semaphores[s_buffer_count];
        vk::Semaphore               _draw_complete_semaphores[s_buffer_count];
        vk::Semaphore               _image_ownership_semaphores[s_buffer_count];
        vk::ImageView               _image_views[s_buffer_count];
    };
}

#endif
