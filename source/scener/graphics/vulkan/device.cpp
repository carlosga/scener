#include "scener/graphics/vulkan/device.hpp"

namespace scener::graphics::vulkan
{
    device::device(const vk::Device& device, const vk::Queue& graphics_queue, const vk::Queue& present_queue) noexcept
        : _device         { std::make_unique<vk::Device>(device) }
        , _graphics_queue { graphics_queue }
        , _present_queue  { present_queue }
    {
        create_sync_primitives();
    }

    device::~device() noexcept
    {
        if (_device.get() != nullptr)
        {
            destroy_sync_primitives();
            _device->destroy(nullptr);
        }
    }

    const vk::Queue& device::graphics_queue() const noexcept
    {
        return _graphics_queue;
    }

    const vk::Queue& device::present_queue() const noexcept
    {
        return _present_queue;
    }

    void device::create_sync_primitives() noexcept
    {
        // Create semaphores to synchronize acquiring presentable buffers before
        // rendering and waiting for drawing to be complete before presenting
        const auto semaphoreCreateInfo = vk::SemaphoreCreateInfo();

        // Create fences that we can use to throttle if we get too far
        // ahead of the image presents
        const auto fence_ci = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);
        for (uint32_t i = 0; i < s_frame_lag; i++) 
        {
            _device->createFence(&fence_ci, nullptr, &_fences[i]);
            auto result = _device->createSemaphore(&semaphoreCreateInfo, nullptr, &_image_acquired_semaphores[i]);
            assert(result == vk::Result::eSuccess);

            result = _device->createSemaphore(&semaphoreCreateInfo, nullptr, &_draw_complete_semaphores[i]);
            assert(result == vk::Result::eSuccess);

            result = _device->createSemaphore(&semaphoreCreateInfo, nullptr, &_image_ownership_semaphores[i]);
            assert(result == vk::Result::eSuccess);
        }
    }

    void device::destroy_sync_primitives() noexcept
    {
        _device->waitIdle();

        // Wait for fences from present operations
        for (uint32_t i = 0; i < s_frame_lag; i++) 
        {
            _device->waitForFences(1, &_fences[i], VK_TRUE, UINT64_MAX);
            _device->destroyFence(_fences[i], nullptr);
            _device->destroySemaphore(_image_acquired_semaphores[i], nullptr);
            _device->destroySemaphore(_draw_complete_semaphores[i], nullptr);
            _device->destroySemaphore(_image_ownership_semaphores[i], nullptr);
        }
    }
}
