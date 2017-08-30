#include "scener/graphics/vulkan/logical_device.hpp"

#include "scener/graphics/vulkan/display_surface.hpp"

namespace scener::graphics::vulkan
{
    logical_device::logical_device(const vk::Device&           device
                                 , std::uint32_t               graphics_queue_family_index
                                 , const vk::Queue&            graphics_queue
                                 , std::uint32_t               present_queue_family_index
                                 , const vk::Queue&            present_queue
                                 , const vk::SurfaceFormatKHR& surface_format
                                 , const vk::PresentModeKHR&   present_mode) noexcept
        : _logical_device              { std::make_unique<vk::Device>(device) }
        , _graphics_queue_family_index { graphics_queue_family_index }
        , _graphics_queue              { graphics_queue }
        , _present_queue_family_index  { present_queue_family_index }
        , _present_queue               { present_queue }
        , _surface_format              { surface_format }
        , _present_mode                { present_mode }
    {
        create_sync_primitives();
        create_command_pool();
        create_command_buffer();
    }

    logical_device::~logical_device() noexcept
    {
        if (_logical_device.get() != nullptr)
        {
            destroy_sync_primitives();

            _logical_device->freeCommandBuffers(_command_pool, s_buffer_count, &_command_buffer);
            _logical_device->destroyCommandPool(_command_pool, nullptr);
            _logical_device->destroy(nullptr);
        }
    }

    const vk::Queue& logical_device::graphics_queue() const noexcept
    {
        return _graphics_queue;
    }

    const vk::Queue& logical_device::present_queue() const noexcept
    {
        return _present_queue;
    }

    void logical_device::create_swap_chain(gsl::not_null<const display_surface*> surface) noexcept
    {
        // https://www.fasterthan.life/blog/2017/7/12/i-am-graphics-and-so-can-you-part-3-breaking-ground

        auto extent     = surface->get_extent();
        auto chain_info = vk::SwapchainCreateInfoKHR()
            .setSurface(surface->_vk_surface)
            .setMinImageCount(s_buffer_count)
            .setImageFormat(_surface_format.format)
            .setImageExtent(extent)
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferSrc)
            // We just want to leave the image as is.
            .setPreTransform(vk::SurfaceTransformFlagBitsKHR::eIdentity)
            .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
            .setPresentMode(_present_mode)
            // Is Vulkan allowed to discard operations outside of the renderable space?
            .setClipped(VK_TRUE);

        // If the graphics queue family and present family don't match then we need to create the swapchain with different information.
        if (_graphics_queue_family_index != _present_queue_family_index)
        {
            std::vector<uint32_t> indices = { _graphics_queue_family_index, _present_queue_family_index };
            
            // There are only two sharing modes.  This is the one to use
            // if images are not exclusive to one queue.
            chain_info
                .setImageSharingMode(vk::SharingMode::eConcurrent)
                .setQueueFamilyIndexCount(2)
                .setPQueueFamilyIndices(indices.data());
        }
        else 
        {
            // If the indices are the same, then the queue can have exclusive access to the images.
            chain_info
                .setImageSharingMode(vk::SharingMode::eExclusive);
        }

        vk::SwapchainKHR swap_chain;

        auto result = _logical_device->createSwapchainKHR(&chain_info, nullptr, &swap_chain);

        assert(result == vk::Result::eSuccess);
    
        // Retrieve the swapchain images from the device.
        // Note that VkImage is simply a handle like everything else.

        // First call gets numImages.
        std::uint32_t num_images = 0;
        
        result = _logical_device->getSwapchainImagesKHR(swap_chain, &num_images, nullptr);

        assert(result == vk::Result::eSuccess);
        assert(num_images > 0);

        std::vector<vk::Image> swap_chain_images(num_images);
        result = _logical_device->getSwapchainImagesKHR(swap_chain, &num_images, swap_chain_images.data());
        
        assert(result == vk::Result::eSuccess);
        assert(num_images > 0);
        
        // Image Views
        //
        // Much like the logical device is an interface to the physical device,
        // image views are interfaces to actual images.  Think of it as this.
        // The image exists outside of you.  But the view is your personal view 
        // ( how you perceive ) the image.
        for (std::uint32_t i = 0; i < s_buffer_count; ++i)
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

            result = _logical_device->createImageView(&image_view_create_info, nullptr, &image_view);

            assert(result == vk::Result::eSuccess);

            _image_views[i] = std::move(image_view);
        }
    }

    void logical_device::create_command_pool() noexcept
    {
        auto create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_graphics_queue_family_index);
       
        auto result = _logical_device->createCommandPool(&create_info, nullptr, &_command_pool);
       
        assert(result == vk::Result::eSuccess);
    }

    void logical_device::create_command_buffer() noexcept
    {
        auto allocate_info = vk::CommandBufferAllocateInfo()
            .setLevel(vk::CommandBufferLevel::ePrimary)
            .setCommandPool(_command_pool)
            .setCommandBufferCount(s_buffer_count);
        
        auto result = _logical_device->allocateCommandBuffers(&allocate_info, &_command_buffer);
    
        assert(result == vk::Result::eSuccess);
    }

    void logical_device::create_sync_primitives() noexcept
    {
        // Create semaphores to synchronize acquiring presentable buffers before
        // rendering and waiting for drawing to be complete before presenting
        const auto semaphoreCreateInfo = vk::SemaphoreCreateInfo();

        // Create fences that we can use to throttle if we get too far
        // ahead of the image presents
        const auto fence_ci = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);
        for (std::uint32_t i = 0; i < s_buffer_count; i++)
        {
            auto result = _logical_device->createFence(&fence_ci, nullptr, &_fences[i]);
            assert(result == vk::Result::eSuccess);

            result = _logical_device->createSemaphore(&semaphoreCreateInfo, nullptr, &_image_acquired_semaphores[i]);
            assert(result == vk::Result::eSuccess);

            result = _logical_device->createSemaphore(&semaphoreCreateInfo, nullptr, &_draw_complete_semaphores[i]);
            assert(result == vk::Result::eSuccess);

            result = _logical_device->createSemaphore(&semaphoreCreateInfo, nullptr, &_image_ownership_semaphores[i]);
            assert(result == vk::Result::eSuccess);
        }
    }

    void logical_device::destroy_sync_primitives() noexcept
    {
        _logical_device->waitIdle();

        // Wait for fences from present operations
        for (std::uint32_t i = 0; i < s_buffer_count; i++)
        {
            _logical_device->waitForFences(1, &_fences[i], VK_TRUE, UINT64_MAX);
            _logical_device->destroyFence(_fences[i], nullptr);
            _logical_device->destroySemaphore(_image_acquired_semaphores[i], nullptr);
            _logical_device->destroySemaphore(_draw_complete_semaphores[i], nullptr);
            _logical_device->destroySemaphore(_image_ownership_semaphores[i], nullptr);
        }
    }
}
