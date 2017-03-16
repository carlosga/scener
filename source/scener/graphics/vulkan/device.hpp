#ifndef SCENER_GRAPHICS_VULKAN_DEVICE_HPP
#define SCENER_GRAPHICS_VULKAN_DEVICE_HPP

#include <vulkan/vulkan.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace scener::graphics::vulkan
{
    class device final
    {
        inline const static std::uint32_t s_frame_lag = 2;

    public:
        device(const vk::Device& device, const vk::Queue& graphics_queue, const vk::Queue& present_queue) noexcept;
        ~device() noexcept;

    public:
        const vk::Queue& graphics_queue() const noexcept;
        const vk::Queue& present_queue() const noexcept;

    private:
        void create_sync_primitives() noexcept;
        void destroy_sync_primitives() noexcept;

    private:
        std::unique_ptr<vk::Device> _device;
        vk::Queue                   _graphics_queue;
        vk::Queue                   _present_queue;
        vk::Fence                   _fences[s_frame_lag];
        vk::Semaphore               _image_acquired_semaphores[s_frame_lag];
        vk::Semaphore               _draw_complete_semaphores[s_frame_lag];
        vk::Semaphore               _image_ownership_semaphores[s_frame_lag];
        
    };
}

#endif
