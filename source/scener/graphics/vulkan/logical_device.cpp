#include "scener/graphics/vulkan/logical_device.hpp"

#include <gsl/gsl>

#include "scener/graphics/vulkan/platform.hpp"

namespace scener::graphics::vulkan
{
    logical_device::logical_device(const vk::Device&                 device
                                 , const memory_allocator&           allocator
                                 , std::uint32_t                     graphics_queue_family_index
                                 , std::uint32_t                     present_queue_family_index
                                 , const vk::SurfaceCapabilitiesKHR& surface_capabilities
                                 , const vk::SurfaceFormatKHR&       surface_format
                                 , const vk::PresentModeKHR&         present_mode
                                 , const vk::FormatProperties&       format_properties) noexcept
        : _logical_device              { device }
        , _allocator                   { allocator }
        , _graphics_queue_family_index { graphics_queue_family_index }
        , _graphics_queue              { }
        , _present_queue_family_index  { present_queue_family_index }
        , _present_queue               { }
        , _surface_capabilities        { surface_capabilities }
        , _surface_format              { surface_format }
        , _present_mode                { present_mode }
        , _format_properties           { format_properties }
        , _command_pool                { }
        , _command_buffers             { surface_capabilities.minImageCount }
        , _fences                      { surface_capabilities.minImageCount }
        , _image_acquired_semaphores   { surface_capabilities.minImageCount }
        , _draw_complete_semaphores    { surface_capabilities.minImageCount }
        , _image_ownership_semaphores  { surface_capabilities.minImageCount }
        , _image_views                 { surface_capabilities.minImageCount }
    {
        get_device_queues();
        create_command_pool();
        create_command_buffer();
        create_sync_primitives();
    }

    logical_device::~logical_device() noexcept
    {
        destroy_sync_primitives();

        _logical_device.freeCommandBuffers(_command_pool, _surface_capabilities.minImageCount, _command_buffers.data());
        _logical_device.destroyCommandPool(_command_pool, nullptr);
        _logical_device.destroy(nullptr);
    }

    const vk::Queue& logical_device::graphics_queue() const noexcept
    {
        return _graphics_queue;
    }

    const vk::Queue& logical_device::present_queue() const noexcept
    {
        return _present_queue;
    }

    void logical_device::create_swap_chain(const render_surface& surface) noexcept
    {
        // https://www.fasterthan.life/blog/2017/7/12/i-am-graphics-and-so-can-you-part-3-breaking-ground

        auto extent     = surface.extent(_surface_capabilities);
        auto chain_info = vk::SwapchainCreateInfoKHR()
            .setClipped(VK_TRUE)
            .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferSrc)
            .setImageArrayLayers(_surface_capabilities.maxImageArrayLayers)
            .setImageExtent(extent)
            .setImageFormat(_surface_format.format)
            .setMinImageCount(_surface_capabilities.minImageCount)
            .setPresentMode(_present_mode)
            .setPreTransform(_surface_capabilities.currentTransform)
            .setSurface(surface.surface());

        std::vector<uint32_t> queue_indices = { _graphics_queue_family_index, _present_queue_family_index };

        // If the graphics queue family and present family don't match then we need to create the swapchain with different information.
        if (_graphics_queue_family_index != _present_queue_family_index)
        {
            // There are only two sharing modes.  This is the one to use
            // if images are not exclusive to one queue.
            chain_info
                .setImageSharingMode(vk::SharingMode::eConcurrent)
                .setQueueFamilyIndexCount(2)
                .setPQueueFamilyIndices(queue_indices.data());
        }
        else
        {
            // If the indices are the same, then the queue can have exclusive access to the images.
            chain_info
                .setImageSharingMode(vk::SharingMode::eExclusive);
        }

        vk::SwapchainKHR swap_chain;

        auto result = _logical_device.createSwapchainKHR(&chain_info, nullptr, &swap_chain);

        check_result(result);

        // Retrieve the swapchain images from the device.
        // Note that VkImage is simply a handle like everything else.

        // First call gets numImages.
        std::uint32_t num_images = 0;

        result = _logical_device.getSwapchainImagesKHR(swap_chain, &num_images, nullptr);

        check_result(result);
        Ensures(num_images > 0);

        std::vector<vk::Image> swap_chain_images(num_images);
        result = _logical_device.getSwapchainImagesKHR(swap_chain, &num_images, swap_chain_images.data());

        check_result(result);
        Ensures(num_images > 0);

        // Image Views
        //
        // Much like the logical device is an interface to the physical device,
        // image views are interfaces to actual images.  Think of it as this.
        // The image exists outside of you.  But the view is your personal view
        // ( how you perceive ) the image.
        for (std::uint32_t i = 0; i < _surface_capabilities.minImageCount; ++i)
        {
            auto subResourceRange = vk::ImageSubresourceRange()
                // There are only 4x aspect bits.  And most people will only use 3x.
                // These determine what is affected by your image operations.
                // VK_IMAGE_ASPECT_COLOR_BIT
                // VK_IMAGE_ASPECT_DEPTH_BIT
                // VK_IMAGE_ASPECT_STENCIL_BIT
                .setAspectMask(vk::ImageAspectFlagBits::eColor)
                // For beginners - a base mip level of zero is par for the course.
                .setBaseMipLevel(0)
                // Level count is the # of images visible down the mip chain.
                // So basically just 1...
                .setLevelCount(1)
                // We don't have multiple layers to these images.
                .setBaseArrayLayer(0)
                .setLayerCount(1);

            auto component_mapping = vk::ComponentMapping()
                .setR(vk::ComponentSwizzle::eR)
                .setG(vk::ComponentSwizzle::eG)
                .setB(vk::ComponentSwizzle::eB)
                .setA(vk::ComponentSwizzle::eA);

            auto image_view_create_info = vk::ImageViewCreateInfo()
                // Just plug it in
                .setImage(swap_chain_images[i])
                // These are 2D images
                .setViewType(vk::ImageViewType::e2D)
                // The selected format
                .setFormat(_surface_format.format)
                // We don't need to swizzle ( swap around ) any of the  color channels
                .setComponents(component_mapping)
                .setSubresourceRange(subResourceRange);

            // Create the view
            vk::ImageView image_view;

            result = _logical_device.createImageView(&image_view_create_info, nullptr, &image_view);

            check_result(result);

            _image_views[i] = std::move(image_view);
        }
    }

    void logical_device::get_device_queues() noexcept
    {
        _graphics_queue = _logical_device.getQueue(_graphics_queue_family_index, 0);
        _present_queue = _logical_device.getQueue(_present_queue_family_index, 0);
    }

    void logical_device::create_command_pool() noexcept
    {
        auto create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_graphics_queue_family_index)
            .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        auto result = _logical_device.createCommandPool(&create_info, nullptr, &_command_pool);

        check_result(result);
    }

    void logical_device::create_command_buffer() noexcept
    {
        auto allocate_info = vk::CommandBufferAllocateInfo()
            .setCommandPool(_command_pool)
            .setCommandBufferCount(_surface_capabilities.minImageCount)
            .setLevel(vk::CommandBufferLevel::ePrimary);

        _command_buffers.resize(_surface_capabilities.minImageCount);

        auto result = _logical_device.allocateCommandBuffers(&allocate_info, _command_buffers.data());

        check_result(result);
    }

    void logical_device::create_sync_primitives() noexcept
    {
        // Create semaphores to synchronize acquiring presentable buffers before
        // rendering and waiting for drawing to be complete before presenting
        const auto semaphoreCreateInfo = vk::SemaphoreCreateInfo();

        _fences.resize(_surface_capabilities.minImageCount);
        _image_acquired_semaphores.resize(_surface_capabilities.minImageCount);
        _draw_complete_semaphores.resize(_surface_capabilities.minImageCount);
        _image_ownership_semaphores.resize(_surface_capabilities.minImageCount);
    
        // Create fences that we can use to throttle if we get too far
        // ahead of the image presents
        const auto fence_ci = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);
        for (std::uint32_t i = 0; i < _surface_capabilities.minImageCount; ++i)
        {
            _fences.push_back(_logical_device.createFence(fence_ci, nullptr));
            _image_acquired_semaphores.push_back(_logical_device.createSemaphore(semaphoreCreateInfo, nullptr));
            _draw_complete_semaphores.push_back(_logical_device.createSemaphore(semaphoreCreateInfo, nullptr));
            _image_ownership_semaphores.push_back(_logical_device.createSemaphore(semaphoreCreateInfo, nullptr));
        }
    }

    void logical_device::destroy_sync_primitives() noexcept
    {
        _logical_device.waitIdle();

        // Wait for fences from present operations
        for (std::uint32_t i = 0; i < _surface_capabilities.minImageCount; i++)
        {
            _logical_device.waitForFences(1, &_fences[i], VK_TRUE, UINT64_MAX);
            _logical_device.destroyFence(_fences[i], nullptr);
            _logical_device.destroySemaphore(_image_acquired_semaphores[i], nullptr);
            _logical_device.destroySemaphore(_draw_complete_semaphores[i], nullptr);
            _logical_device.destroySemaphore(_image_ownership_semaphores[i], nullptr);
        }
    }
}
