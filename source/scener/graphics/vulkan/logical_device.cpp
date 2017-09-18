// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/logical_device.hpp"

#include <gsl/gsl>

#include "scener/graphics/vulkan/surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"
#include "scener/graphics/vulkan/image.hpp"

namespace scener::graphics::vulkan
{
    using scener::math::basic_color;

    logical_device::logical_device(const vk::PhysicalDevice&         physical_device
                                 , const vk::Device&                 logical_device
                                 , std::uint32_t                     graphics_queue_family_index
                                 , std::uint32_t                     present_queue_family_index
                                 , const vk::SurfaceCapabilitiesKHR& surface_capabilities
                                 , const vk::SurfaceFormatKHR&       surface_format
                                 , const vk::Format&                 depth_format
                                 , const vk::PresentModeKHR&         present_mode
                                 , const vk::FormatProperties&       format_properties) noexcept
        : _logical_device              { logical_device }
        , _allocator                   { physical_device, logical_device }
        , _graphics_queue_family_index { graphics_queue_family_index }
        , _graphics_queue              { }
        , _present_queue_family_index  { present_queue_family_index }
        , _present_queue               { }
        , _surface_capabilities        { surface_capabilities }
        , _surface_format              { surface_format }
        , _depth_format                { depth_format }
        , _present_mode                { present_mode }
        , _format_properties           { format_properties }
        , _command_pool                { }
        , _swap_chain                  { }
        , _render_pass                 { }
        , _swap_chain_images           { surface_capabilities.minImageCount }
        , _swap_chain_image_views      { surface_capabilities.minImageCount }
        , _frame_buffers               { surface_capabilities.minImageCount }
        , _command_buffers             { surface_capabilities.minImageCount }
        , _fences                      { surface_capabilities.minImageCount }
        , _image_acquired_semaphores   { surface_capabilities.minImageCount }
        , _draw_complete_semaphores    { surface_capabilities.minImageCount }
        , _image_ownership_semaphores  { surface_capabilities.minImageCount }
        , _clear_color                 { basic_color<float>::black() }
    {
        get_device_queues();
        create_command_pool();
        create_command_buffers();
        create_sync_primitives();
    }

    logical_device::~logical_device() noexcept
    {
        destroy_sync_primitives();

        if (_command_buffers.size() > 0)
        {
            _logical_device.freeCommandBuffers(_command_pool, _surface_capabilities.minImageCount, _command_buffers.data());
            _command_buffers.clear();
        }

        _logical_device.destroyCommandPool(_command_pool, nullptr);

        for (std::uint32_t i = 0; i < _swap_chain_image_views.size(); ++i)
        {
            _logical_device.destroyImageView(_swap_chain_image_views[i], nullptr);
        }

        _swap_chain_image_views.clear();

        _logical_device.destroySwapchainKHR(_swap_chain, nullptr);

        // swap chain images are destroyed by the vulkan driver
        _swap_chain_images.clear();

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

    const memory_allocator& logical_device::allocator() const noexcept
    {
        return _allocator;
    }

    const scener::math::basic_color<float>& logical_device::clear_color() const noexcept
    {
        return _clear_color;
    }

    void logical_device::clear_color(const scener::math::basic_color<float>& color) noexcept
    {
        _clear_color = color;
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

        // If the graphics queue family and present family don't match then we need to create the
        // swapchain with different information.
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

        _swap_chain = _logical_device.createSwapchainKHR(chain_info, nullptr);

        // Retrieve the swapchain images from the device.
        // Note that VkImage is simply a handle like everything else.

        // First call gets numImages.
        std::uint32_t num_images = 0;

        auto result = _logical_device.getSwapchainImagesKHR(_swap_chain, &num_images, nullptr);

        check_result(result);
        Ensures(num_images > 0);

        _swap_chain_images.resize(num_images);
        result = _logical_device.getSwapchainImagesKHR(_swap_chain, &num_images, _swap_chain_images.data());

        check_result(result);
        Ensures(num_images > 0);

        // Image Views
        //
        // Much like the logical device is an interface to the physical device,
        // image views are interfaces to actual images.  Think of it as this.
        // The image exists outside of you.  But the view is your personal view
        // ( how you perceive ) the image.
        for (std::uint32_t i = 0; i < num_images; ++i)
        {
            auto sub_resource_range = vk::ImageSubresourceRange()
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
                .setImage(_swap_chain_images[i])
                // These are 2D images
                .setViewType(vk::ImageViewType::e2D)
                // The selected format
                .setFormat(_surface_format.format)
                // We don't need to swizzle ( swap around ) any of the  color channels
                .setComponents(component_mapping)
                .setSubresourceRange(sub_resource_range);

            // Create the view
            result = _logical_device.createImageView(&image_view_create_info, nullptr, &_swap_chain_image_views[i]);

            check_result(result);
        }
    }

    void logical_device::create_render_targets(const scener::math::basic_size<std::uint32_t>& size) noexcept
    {
    }

    void logical_device::record_command_buffers() const noexcept
    {
        auto begin_info = vk::CommandBufferBeginInfo()
            .setFlags(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

        auto clear_color = vk::ClearColorValue()
            .setFloat32(_clear_color.components);

        auto image_subresource_range = vk::ImageSubresourceRange()
            .setBaseMipLevel(0)
            .setLevelCount(1)
            .setBaseArrayLayer(0)
            .setLayerCount(1);

        for (std::uint32_t i = 0; i < _swap_chain_images.size(); ++i)
        {
            const auto& command_buffer   = _command_buffers[i];
            const auto& swap_chain_image = _swap_chain_images[i];

            auto barrier_from_present_to_clear = vk::ImageMemoryBarrier()
                .setSrcAccessMask(vk::AccessFlagBits::eMemoryRead)
                .setDstAccessMask(vk::AccessFlagBits::eMemoryWrite)
                .setNewLayout(vk::ImageLayout::eTransferDstOptimal)
                .setImage(swap_chain_image)
                .setSubresourceRange(image_subresource_range);

            auto barrier_from_clear_to_present = vk::ImageMemoryBarrier()
                .setSrcAccessMask(vk::AccessFlagBits::eTransferWrite)
                .setDstAccessMask(vk::AccessFlagBits::eMemoryRead)
                .setOldLayout(vk::ImageLayout::eTransferDstOptimal)
                .setNewLayout(vk::ImageLayout::ePresentSrcKHR)
                .setImage(swap_chain_image)
                .setSubresourceRange(image_subresource_range);

            auto result = command_buffer.begin(&begin_info);

            check_result(result);

            // present -> clear
            command_buffer.pipelineBarrier(
                vk::PipelineStageFlagBits::eTransfer
              , vk::PipelineStageFlagBits::eTransfer
              , vk::DependencyFlagBits::eViewLocalKHX
              , 0                                       // Memory barriers count
              , nullptr                                 // Memory barriers
              , 0                                       // Memory barriers buffer count
              , nullptr                                 // Memory barriers buffers
              , 1                                       // Image memory barriers count
              , &barrier_from_present_to_clear          // Image memory barriers
            );

            command_buffer.clearColorImage(
                swap_chain_image
              , vk::ImageLayout::eTransferDstOptimal
              , &clear_color
              , 1
              , &image_subresource_range
            );

            // clear -> present
            command_buffer.pipelineBarrier(
                vk::PipelineStageFlagBits::eTransfer
              , vk::PipelineStageFlagBits::eBottomOfPipe
              , vk::DependencyFlagBits::eViewLocalKHX
              , 0                                       // Memory barriers count
              , nullptr                                 // Memory barriers
              , 0                                       // Memory barriers buffer count
              , nullptr                                 // Memory barriers buffers
              , 1                                       // Image memory barriers count
              , &barrier_from_clear_to_present          // Image memory barriers
            );

            command_buffer.end();
        }
    }

    image logical_device::create_image(const image_options& options) const noexcept
    {
        auto internal_format = _surface_format.format;

        // Create Sampler
        create_sampler();

        // Images will always be sampled
        auto depth_image = (options.usage & vk::ImageUsageFlagBits::eDepthStencilAttachment) == vk::ImageUsageFlagBits::eDepthStencilAttachment;
        auto usage_flags = options.usage & vk::ImageUsageFlagBits::eSampled;
        if (!depth_image)
        {
            // For everything else we mark it as a transfer destination.
            // This is because we are copying data to the image.
            usage_flags |= vk::ImageUsageFlagBits::eTransferDst;
        }

        // Create Image
        auto cubic = (options.target == texture_target::texture_cube_map
                   || options.target == texture_target::texture_cube_map_array);

        auto image_create_info = vk::ImageCreateInfo()
            .setImageType(vk::ImageType::e2D)
            .setExtent(options.extent)
            .setMipLevels(options.mip_levels)
            .setArrayLayers(cubic ? 6 : 1)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setTiling(vk::ImageTiling::eOptimal)
            .setUsage(usage_flags);

        if (cubic)
        {
            image_create_info.setFlags(vk::ImageCreateFlagBits::eCubeCompatible);
        }

        // In Vulkan images have layouts which determine what sorts of operations can
        // be performed on it at any given time.  The other reason is it helps the hardware
        // optimize access to the image data for certain tasks.
        // Here we are starting out undefined, simply because we'll be transitioning the
        // image again during upload.
        image_create_info.setInitialLayout(vk::ImageLayout::eUndefined);

        // Unless this is a render target we don't need to worry about sharing it.
        image_create_info.setSharingMode(vk::SharingMode::eExclusive);

        // Create the image
        vk::Image image = _allocator.allocate_image(image_create_info);

        // Create Image View
        // As mentioned in Part 3 ( again in the swapchain function ) views are how you interface with a given image.
        // You can think of the VkImage as the actual data and VkImageView as your view into the image.

        vk::ImageView image_view;

        auto subresource_range = vk::ImageSubresourceRange()
            .setAspectMask(depth_image ? vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil : vk::ImageAspectFlagBits::eColor)
            .setBaseMipLevel(0)
            .setLevelCount(options.mip_levels)
            .setBaseArrayLayer(0)
            .setLayerCount(cubic ? 6 : 1)
            .setBaseMipLevel(0);

        auto component_mapping = vk::ComponentMapping()
            .setR(vk::ComponentSwizzle::eR)
            .setG(vk::ComponentSwizzle::eG)
            .setB(vk::ComponentSwizzle::eB)
            .setA(vk::ComponentSwizzle::eA);

        auto view_create_info = vk::ImageViewCreateInfo()
            .setImage(image)
            .setViewType(cubic ? vk::ImageViewType::eCube : vk::ImageViewType::e2D)
            .setFormat(internal_format)
            .setComponents(component_mapping)
            .setSubresourceRange(subresource_range);

        auto result = _logical_device.createImageView(&view_create_info, nullptr, &image_view);

        check_result(result);

        return { std::move(image), std::move(image_view) };
    }

    void logical_device::create_sampler() const noexcept
    {

    }

    void logical_device::get_device_queues() noexcept
    {
        _logical_device.getQueue(_graphics_queue_family_index, 0, &_graphics_queue);
        _logical_device.getQueue(_present_queue_family_index, 0, &_present_queue);
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
            auto result = _logical_device.createFence(&fence_ci, nullptr, &_fences[i]);
            check_result(result);

            result = _logical_device.createSemaphore(&semaphoreCreateInfo, nullptr, &_image_acquired_semaphores[i]);
            check_result(result);

            result = _logical_device.createSemaphore(&semaphoreCreateInfo, nullptr, &_draw_complete_semaphores[i]);
            check_result(result);

            result = _logical_device.createSemaphore(&semaphoreCreateInfo, nullptr, &_image_ownership_semaphores[i]);
            check_result(result);
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

        _fences.clear();
        _image_acquired_semaphores.clear();
        _draw_complete_semaphores.clear();
        _draw_complete_semaphores.clear();
        _image_ownership_semaphores.clear();
    }

    void logical_device::create_command_pool() noexcept
    {
        auto create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_graphics_queue_family_index)
            .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        auto result = _logical_device.createCommandPool(&create_info, nullptr, &_command_pool);

        check_result(result);
    }

    void logical_device::create_command_buffers() noexcept
    {
        auto allocate_info = vk::CommandBufferAllocateInfo()
            .setCommandPool(_command_pool)
            .setCommandBufferCount(_surface_capabilities.minImageCount)
            .setLevel(vk::CommandBufferLevel::ePrimary);

        _command_buffers.resize(_surface_capabilities.minImageCount);

        auto result = _logical_device.allocateCommandBuffers(&allocate_info, _command_buffers.data());

        check_result(result);
    }

    void logical_device::create_frame_buffers() noexcept
    {
    }

    void logical_device::create_render_pass() noexcept
    {
        std::vector<vk::AttachmentDescription> attachments(2);

        // For the color attachment, we'll simply be using the swapchain images.
        auto colorAttachment = vk::AttachmentDescription()
            .setFormat(_surface_format.format)
            // Sample count goes from 1 - 64
            .setSamples(vk::SampleCountFlagBits::e1)
            // I don't care what you do with the image memory when you load it for use.
            .setLoadOp(vk::AttachmentLoadOp::eDontCare)
            // Just store the image when you go to store it.
            .setStoreOp(vk::AttachmentStoreOp::eStore)
            // I don't care what the initial layout of the image is.
            .setInitialLayout(vk::ImageLayout::eUndefined)
            // It better be ready to present to the user when we're done with the renderpass.
            .setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

        attachments.push_back(colorAttachment);

        // For the depth attachment, we'll be using the device depth format.
        auto depthAttachment = vk::AttachmentDescription()
            .setFormat(_depth_format)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStoreOp(vk::AttachmentStoreOp::eDontCare)
            .setInitialLayout(vk::ImageLayout::eUndefined)
            .setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        attachments.push_back(depthAttachment);

        // Now we enumerate the attachments for a subpass.  We have to have at least one subpass.
        auto colorRef = vk::AttachmentReference()
            .setAttachment(0)
            .setLayout(vk::ImageLayout::eColorAttachmentOptimal);

        auto depthRef = vk::AttachmentReference()
            .setAttachment(1)
            .setLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        // Basically is this graphics or compute
        auto subpass = vk::SubpassDescription()
            .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
            .setColorAttachmentCount(1)
            .setPColorAttachments(&colorRef)
            .setPDepthStencilAttachment(&depthRef);

        auto renderPassCreateInfo = vk::RenderPassCreateInfo()
            .setAttachmentCount(attachments.size())
            .setPAttachments(attachments.data())
            .setSubpassCount(1)
            .setPSubpasses(&subpass)
            .setDependencyCount(0);

        auto result = _logical_device.createRenderPass(&renderPassCreateInfo, NULL, &_render_pass);

        check_result(result);

        create_frame_buffers();
    }
}