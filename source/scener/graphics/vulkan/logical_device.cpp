// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/logical_device.hpp"

#include <string>
#include <gsl/gsl>

#include "scener/graphics/fill_mode.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/vertex_element_format.hpp"
#include "scener/graphics/vertex_buffer.hpp"
#include "scener/graphics/vulkan/shader_stage.hpp"
#include "scener/graphics/vulkan/surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"
#include "scener/math/basic_rect.hpp"

namespace scener::graphics::vulkan
{
    using scener::graphics::vertex_element_format;
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
        , _graphics_queue_family_index { graphics_queue_family_index }
        , _graphics_queue              { }
        , _present_queue_family_index  { present_queue_family_index }
        , _present_queue               { }
        , _surface_capabilities        { surface_capabilities }
        , _surface_format              { surface_format }
        , _present_mode                { present_mode }
        , _format_properties           { format_properties }
        , _command_pool                { }
        , _single_time_command_pool    { }
        , _swap_chain                  { }
        , _render_pass                 { }
        , _swap_chain_images           { surface_capabilities.minImageCount }
        , _swap_chain_image_views      { surface_capabilities.minImageCount }
        , _frame_buffers               { surface_capabilities.minImageCount }
        , _command_buffers             { surface_capabilities.minImageCount }
        , _single_time_command_buffer  { }
        , _fences                      { surface_capabilities.minImageCount }
        , _single_time_command_fence   { }
        , _image_acquired_semaphores   { surface_capabilities.minImageCount }
        , _draw_complete_semaphores    { surface_capabilities.minImageCount }
        , _image_ownership_semaphores  { surface_capabilities.minImageCount }
        , _clear_color                 { basic_color<float>::black() }
        , _next_command_buffer_index   { 0 }
        , _acquired_image_index        { 0 }
        , _depth_format                { depth_format }
        , _depth_buffer                { nullptr }
        , _allocator                   { }
    {
        create_allocator(physical_device, logical_device);
        get_device_queues();
        create_command_pools();
        create_command_buffers();
        create_sync_primitives();
    }

    logical_device::~logical_device() noexcept
    {
        // Swapchain
        destroy_swap_chain();

        // Command buffers
        destroy_command_buffers();

        // Command pools
        destroy_command_pools();

        // Memory allocators
        vmaDestroyAllocator(_allocator);

        // Logical devices
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

    const scener::math::basic_color<float>& logical_device::clear_color() const noexcept
    {
        return _clear_color;
    }

    void logical_device::clear_color(const scener::math::basic_color<float>& color) noexcept
    {
        _clear_color = color;
    }

    bool logical_device::begin_draw(const render_surface& surface) noexcept
    {
        auto command_buffer_index = _next_command_buffer_index % _swap_chain_images.size();
        auto command_buffer       = _command_buffers[command_buffer_index];

        reset_fence(_fences[command_buffer_index]);

        auto begin_info = vk::CommandBufferBeginInfo()
            .setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        // Begin main command buffer
        command_buffer.begin(&begin_info);

        // Acquire swapchain image
        _acquired_image_index = 0;
        auto result = _logical_device.acquireNextImageKHR(
            _swap_chain
          , UINT64_MAX
          , _image_acquired_semaphores[command_buffer_index]
          , _fences[command_buffer_index]
          , &_acquired_image_index);

        check_result(result);

        const auto clear_color = vk::ClearValue()
            .setColor({ _clear_color.components })
            .setDepthStencil({ 1.0f, 0 });

        auto render_area = vk::Rect2D()
            .setOffset({ 0, 0 })
            .setExtent(surface.extent(_surface_capabilities));

        auto render_pass_begin_info = vk::RenderPassBeginInfo()
            .setRenderPass(_render_pass)
            .setFramebuffer(_frame_buffers[_acquired_image_index])
            .setRenderArea(render_area)
            .setClearValueCount(1)
            .setPClearValues(&clear_color);

        command_buffer.beginRenderPass(&render_pass_begin_info, vk::SubpassContents::eInline);

        return false;
    }

    void logical_device::bind_graphics_pipeline(const vk::Pipeline& pipeline) noexcept
    {
        const auto command_buffer_index = _next_command_buffer_index % _swap_chain_images.size();

        _command_buffers[command_buffer_index].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
    }

    void logical_device::draw_indexed(graphics::primitive_type       primitive_type
                                    , std::uint32_t                  base_vertex
                                    , std::uint32_t                  min_vertex_index
                                    , std::uint32_t                  num_vertices
                                    , std::uint32_t                  start_index
                                    , std::uint32_t                  primitive_count
                                    , const graphics::vertex_buffer* vertex_buffer
                                    , const graphics::index_buffer*  index_buffer) noexcept
    {
        auto command_buffer_index = _next_command_buffer_index % _swap_chain_images.size();
        auto command_buffer       = _command_buffers[command_buffer_index];
        auto index_element_type   = static_cast<vk::IndexType>(index_buffer->index_element_type());
        auto offset               = start_index * index_buffer->element_size_in_bytes();

        // Vertex buffer binding
        command_buffer.bindVertexBuffers(0, 1, &vertex_buffer->_buffer.memory_buffer(), nullptr);

        // Index buffer binding
        command_buffer.bindIndexBuffer(index_buffer->_buffer.memory_buffer(), 0, index_element_type);

        // Draw call
        command_buffer.drawIndexed(
            index_buffer->index_count()
          , get_element_count(primitive_type, primitive_count)
          , start_index
          , offset
          , base_vertex);
    }

    void logical_device::end_draw(const render_surface& surface) noexcept
    {
        auto command_buffer_index = _next_command_buffer_index % _swap_chain_images.size();
        auto command_buffer       = _command_buffers[command_buffer_index];

        command_buffer.endRenderPass();
        command_buffer.end();

        _next_command_buffer_index++;
    }

    void logical_device::present(const render_surface& surface) noexcept
    {
        // Submit command buffer
        static const vk::PipelineStageFlags submit_wait_stages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

        auto submit_info = vk::SubmitInfo()
            .setWaitSemaphoreCount(static_cast<std::uint32_t>(_image_ownership_semaphores.size()))
            .setPWaitSemaphores(_image_ownership_semaphores.data())
            .setPWaitDstStageMask(submit_wait_stages)
            .setSignalSemaphoreCount(static_cast<std::uint32_t>(_draw_complete_semaphores.size()))
            .setPWaitSemaphores(_draw_complete_semaphores.data())
            .setCommandBufferCount(static_cast<std::uint32_t>(_command_buffers.size()))
            .setPCommandBuffers(_command_buffers.data());

        check_result(_graphics_queue.submit(1, &submit_info, _fences[_acquired_image_index]));

        auto present_info = vk::PresentInfoKHR()
            .setWaitSemaphoreCount(static_cast<std::uint32_t>(_draw_complete_semaphores.size()))
            .setPWaitSemaphores(_draw_complete_semaphores.data())
            .setSwapchainCount(1)
            .setPSwapchains(&_swap_chain)
            .setPImageIndices(&_acquired_image_index);

        auto result = _graphics_queue.presentKHR(&present_info);

        check_result(result);
    }

    buffer logical_device::create_index_buffer(const gsl::span<const std::uint8_t>& data) noexcept
    {
        return create_buffer(buffer_usage::index_buffer | buffer_usage::transfer_destination
                           , vk::SharingMode::eExclusive
                           , data);
    }

    buffer logical_device::create_vertex_buffer(const gsl::span<const std::uint8_t>& data) noexcept
    {
        return create_buffer(buffer_usage::vertex_buffer | buffer_usage::transfer_destination
                           , vk::SharingMode::eExclusive
                           , data);
    }

    buffer logical_device::create_uniform_buffer(std::uint64_t count) noexcept
    {
        buffer buffer_instance { buffer_usage::uniform_buffer | buffer_usage::transfer_destination
                               , vk::SharingMode::eExclusive, count, &_allocator };

        return buffer_instance;
    }

    buffer logical_device::create_buffer(buffer_usage usage, vk::SharingMode sharing_mode, const gsl::span<const std::uint8_t>& data) noexcept
    {
        buffer buffer_instance { usage, sharing_mode, static_cast<std::uint64_t>(data.size()), &_allocator };

        if (data.size() > 0)
        {
            if ((usage & buffer_usage::transfer_destination) == buffer_usage::transfer_destination)
            {
                VkBufferCreateInfo buffer_create_info = {
                    VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO        // VkStructureType
                  , nullptr                                     // pNext
                  , 0                                           // flags
                  , buffer_instance.size()                      // size
                  , VK_BUFFER_USAGE_TRANSFER_SRC_BIT            // usage
                  , static_cast<VkSharingMode>(sharing_mode)    // sharingMode
                  , 0                                           // queueFamilyIndexCount
                  , nullptr                                     // pQueueFamilyIndices
                };

                VmaAllocationCreateInfo allocation_create_info = { };

                allocation_create_info.usage = VMA_MEMORY_USAGE_CPU_ONLY;
                allocation_create_info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;

                vk::Buffer        staging_buffer            = { };
                VmaAllocation     staging_buffer_allocation;
                VmaAllocationInfo staging_buffer_alloc_info = { };
                auto result = vmaCreateBuffer(
                    _allocator
                  , &buffer_create_info
                  , &allocation_create_info
                  , reinterpret_cast<VkBuffer*>(&staging_buffer)
                  , &staging_buffer_allocation
                  , &staging_buffer_alloc_info);

                Ensures(result == VK_SUCCESS);

                std::copy_n(data.data(), data.size(), reinterpret_cast<char*>(staging_buffer_alloc_info.pMappedData));

                // Copy buffer contents from the staging buffer to the real buffer
                auto buffer_copy_region = vk::BufferCopy()
                    .setSrcOffset(0)
                    .setDstOffset(0)
                    .setSize(buffer_create_info.size);

                // Copy buffer contents from the staging buffer to the real buffer
                begin_single_time_commands();

                _single_time_command_buffer.copyBuffer(staging_buffer, buffer_instance.memory_buffer(), 1, &buffer_copy_region);

                end_single_time_commands();

                // Destroy the staging buffer
                vmaDestroyBuffer(_allocator, staging_buffer, staging_buffer_allocation);
            }
            else
            {
                buffer_instance.set_data(0, static_cast<std::uint64_t>(data.size()), data.data());
            }
        }

        return buffer_instance;
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
                // Level count is the # of images visible down the mip chain.
                // So basically just 1...
                .setLevelCount(1)
                // We don't have multiple layers to these images.
                .setLayerCount(1);

            auto component_mapping = vk::ComponentMapping()
                .setR(vk::ComponentSwizzle::eIdentity)
                .setG(vk::ComponentSwizzle::eIdentity)
                .setB(vk::ComponentSwizzle::eIdentity)
                .setA(vk::ComponentSwizzle::eIdentity);

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

        // Render pass
        create_render_pass();

        // Depth buffer
        create_depth_buffer(extent);

        // Frame buffers
        create_frame_buffers(extent);
    }

    void logical_device::recreate_swap_chain(const render_surface& surface) noexcept
    {
//        _logical_device.waitIdle();
//        destroy_swap_chain(false);
//        create_sync_primitives();
//        create_swap_chain(surface);
    }

    vk::UniquePipeline logical_device::create_graphics_pipeline(
          graphics::primitive_type                            primitive_type
        , const graphics::viewport&                           viewport_state
        , const gsl::not_null<vertex_buffer*>                 vertex_buffer
        , const graphics::blend_state&                        color_blend_state
        , const graphics::depth_stencil_state&                depth_stencil_state
        , const graphics::rasterizer_state&                   rasterization_state
        , const std::vector<std::shared_ptr<vulkan::shader>>& shaders) noexcept
    {
        // Viewport
        auto viewport = vk::Viewport()
            .setX(viewport_state.rect.x())
            .setY(viewport_state.rect.y())
            .setWidth(viewport_state.rect.width())
            .setHeight(viewport_state.rect.height())
            .setMinDepth(viewport_state.min_depth)
            .setMaxDepth(viewport_state.max_depth);

        auto scissor = vk::Rect2D()
            .setOffset({ static_cast<std::int32_t>(viewport_state.rect.x())
                       , static_cast<std::int32_t>(viewport_state.rect.y()) })
            .setExtent({ viewport_state.rect.width(), viewport_state.rect.height() });

        auto viewport_state_create_info = vk::PipelineViewportStateCreateInfo()
            .setViewportCount(1)
            .setPViewports(&viewport)
            .setScissorCount(1)
            .setPScissors(&scissor);

        // Color blend, depth stencil and rasterier states
        auto blend_attachment                = vk::PipelineColorBlendAttachmentState();
        auto color_blend_state_create_info   = vk_color_blend_state(color_blend_state, blend_attachment);
        auto depth_stencil_state_create_info = vk_depth_stencil_state(depth_stencil_state);
        auto rasterizer_state_create_info    = vk_rasterizer_state(rasterization_state);

        // Multisampling state
        auto multisampling_create_info = vk::PipelineMultisampleStateCreateInfo()
            .setSampleShadingEnable(rasterization_state.multi_sample_anti_alias)
            .setRasterizationSamples(vk::SampleCountFlagBits::e1)
            .setMinSampleShading(1.0f)
            .setPSampleMask(nullptr)
            .setAlphaToCoverageEnable(false)
            .setAlphaToOneEnable(false);

        // Dynamic states
        vk::DynamicState dynamic_states[] = {
            vk::DynamicState::eViewport
          , vk::DynamicState::eLineWidth
        };

        auto dynamic_states_create_info = vk::PipelineDynamicStateCreateInfo()
            .setDynamicStateCount(2)
            .setPDynamicStates(dynamic_states);

        // Shader stages
        std::vector<vk::ShaderModule>                  shader_modules;
        std::vector<vk::PipelineShaderStageCreateInfo> shader_stages;

        for (const auto& shader : shaders)
        {
            auto create_info = vk::ShaderModuleCreateInfo()
                .setCodeSize(shader->buffer().size())
                .setPCode(reinterpret_cast<const std::uint32_t*>(shader->buffer().data()));

            auto module = _logical_device.createShaderModule(create_info, nullptr);

            shader_modules.push_back(module);

            const auto stageFlags = static_cast<vk::ShaderStageFlagBits>(shader->stage());

            auto stage = vk::PipelineShaderStageCreateInfo()
                .setModule(module)
                .setStage(stageFlags)
                .setPName(shader->entry_point().c_str());

            shader_stages.push_back(stage);
        }

        // Pipeline layout
        std::vector<vk::DescriptorSetLayout> pipelineLayouts;
        std::vector<vk::PushConstantRange> constantRanges;

        auto pipeline_layout_create_info = vk::PipelineLayoutCreateInfo()
            .setSetLayoutCount(static_cast<std::uint32_t>(pipelineLayouts.size()))
            .setPSetLayouts(pipelineLayouts.data())
            .setPushConstantRangeCount(static_cast<std::uint32_t>(constantRanges.size()))
            .setPPushConstantRanges(constantRanges.data());

        vk::PipelineLayout pipeline_layout;

        auto result = _logical_device.createPipelineLayout(&pipeline_layout_create_info, nullptr, &pipeline_layout);

        check_result(result);

        // Assembly state
        vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState { };

        inputAssemblyState.setTopology(static_cast<vk::PrimitiveTopology>(primitive_type));

        // Vertex buffer
        vk::PipelineVertexInputStateCreateInfo pipelineVertexInput { };

        const auto& vertex_declaration = vertex_buffer->vertex_declaration();

        vk::VertexInputBindingDescription vertexInputBinding { };

        vertexInputBinding.setBinding(0);
        vertexInputBinding.setStride(vertex_declaration.vertex_stride());
        vertexInputBinding.setInputRate(vk::VertexInputRate::eVertex);

        std::vector<vk::VertexInputAttributeDescription> vertexAttributes;

        std::for_each(vertex_declaration.vertex_elements().begin()
                    , vertex_declaration.vertex_elements().end()
                    , [&] (const auto& element) {
                        vk::VertexInputAttributeDescription attr;

                        attr.setBinding(0);
                        attr.setLocation(element.usage_index());
                        attr.setOffset(element.offset());

                        switch (element.format())
                        {
                        case vertex_element_format::single: ///< Single-component, 32-bit floating-point, expanded to (float, 0, 0, 1).
                            attr.setFormat(vk::Format::eR32Sfloat);
                            break;
                        case vertex_element_format::vector2           : ///< Two-component, 32-bit floating-point, expanded to (float, float, 0, 1).
                            attr.setFormat(vk::Format::eR32G32Sfloat);
                            break;
                        case vertex_element_format::vector3           : ///< Three-component, 32-bit floating point, expanded to (float, float, float, 1).
                            attr.setFormat(vk::Format::eR32G32B32Sfloat);
                            break;
                        case vertex_element_format::vector4           : ///< Four-component, 32-bit floating point, expanded to (float, float, float, float).
                            attr.setFormat(vk::Format::eR32G32B32A32Sfloat);
                            break;
                        case vertex_element_format::color             : ///< Four-component, packed, unsigned byte, mapped to 0 to 1 range.
                            attr.setFormat(vk::Format::eR32G32B32A32Sfloat);
                            break;
                        case vertex_element_format::byte4             : ///< Four-component, unsigned byte.
                            attr.setFormat(vk::Format::eR8Srgb);
                            break;
                        case vertex_element_format::short2            : ///< Two-component, signed short expanded to (value, value, 0, 1).
                            attr.setFormat(vk::Format::eR16G16Sint);
                            break;
                        case vertex_element_format::short4            : ///< Four-component, signed short expanded to (value, value, value, value).
                            attr.setFormat(vk::Format::eR16G16B16A16Sint);
                            break;
                        }

                        vertexAttributes.push_back(attr);
                      });

        pipelineVertexInput.setPVertexBindingDescriptions(&vertexInputBinding);
        pipelineVertexInput.setVertexBindingDescriptionCount(1);

        pipelineVertexInput.setPVertexAttributeDescriptions(vertexAttributes.data());
        pipelineVertexInput.setVertexAttributeDescriptionCount(static_cast<uint32_t>(vertexAttributes.size()));

        // Graphics pipeline
        auto pipeline_create_info = vk::GraphicsPipelineCreateInfo()
            .setRenderPass(_render_pass)
            .setSubpass(0)
            .setPInputAssemblyState(&inputAssemblyState)
            .setPVertexInputState(&pipelineVertexInput)
            .setStageCount(static_cast<std::uint32_t>(shader_stages.size()))
            .setPStages(shader_stages.data())
            .setLayout(pipeline_layout)
            .setPColorBlendState(&color_blend_state_create_info)
            .setPDepthStencilState(&depth_stencil_state_create_info)
            .setPRasterizationState(&rasterizer_state_create_info)
            .setPMultisampleState(&multisampling_create_info)
            .setPViewportState(&viewport_state_create_info)
            .setPDynamicState(&dynamic_states_create_info);

        // Graphics pipeline initialization
        auto cache    = vk::PipelineCache();
        auto pipeline = _logical_device.createGraphicsPipelineUnique(cache, pipeline_create_info, nullptr);

        std::for_each(shader_modules.begin(), shader_modules.end(), [&] (auto& module) {
            _logical_device.destroyShaderModule(module, nullptr);
        });

        return pipeline;
    }

    std::unique_ptr<image_storage, image_deleter>
    logical_device::create_image(const image_options& options) const noexcept
    {
        // Images will always be sampled
        const auto depth_image = (options.usage & vk::ImageUsageFlagBits::eDepthStencilAttachment) == vk::ImageUsageFlagBits::eDepthStencilAttachment;
        auto usage_flags = options.usage | vk::ImageUsageFlagBits::eSampled;

        if (!depth_image)
        {
            // For everything else we mark it as a transfer destination.
            // This is because we are copying data to the image.
            usage_flags |= vk::ImageUsageFlagBits::eTransferDst;
        }

        // Create Image
        const auto cubic = (options.target == texture_target::texture_cube_map
                         || options.target == texture_target::texture_cube_map_array);

        auto image_create_info = vk::ImageCreateInfo()
            .setFormat(depth_image ? _depth_format : _surface_format.format)
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
        VmaAllocationCreateInfo allocation_create_info = { };

        allocation_create_info.usage = VMA_MEMORY_USAGE_CPU_ONLY;

        vk::Image     image            { };
        VmaAllocation image_allocation { };

        // TODO: Image destroy
        auto create_image_result = vmaCreateImage(
            _allocator
          , reinterpret_cast<const VkImageCreateInfo*>(&image_create_info)
          , &allocation_create_info
          , reinterpret_cast<VkImage*>(&image)
          , &image_allocation
          , nullptr);

        Ensures(create_image_result == VK_SUCCESS);

        // Create Image View

        vk::ImageView image_view;

        const auto subresource_mask = depth_image ? vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil : vk::ImageAspectFlagBits::eColor;
        const auto view_type = cubic ? vk::ImageViewType::eCube : vk::ImageViewType::e2D;

        auto subresource_range = vk::ImageSubresourceRange()
            .setAspectMask(subresource_mask)
            .setBaseMipLevel(0)
            .setLevelCount(options.mip_levels)
            .setBaseArrayLayer(0)
            .setLayerCount(cubic ? 6 : 1);

        auto component_mapping = vk::ComponentMapping()
            .setR(vk::ComponentSwizzle::eR)
            .setG(vk::ComponentSwizzle::eG)
            .setB(vk::ComponentSwizzle::eB)
            .setA(vk::ComponentSwizzle::eA);

        auto view_create_info = vk::ImageViewCreateInfo()
            .setImage(image)
            .setViewType(view_type)
            .setFormat(depth_image ? _depth_format : _surface_format.format)
            .setComponents(component_mapping)
            .setSubresourceRange(subresource_range);

        auto result = _logical_device.createImageView(&view_create_info, nullptr, &image_view);

        check_result(result);

        // TODO: Ugly hack to release the vulkan buffer and its memory allocation at the same time
        auto wrapper = new image_storage(image, image_view, image_allocation);

        return std::unique_ptr<image_storage, image_deleter>(wrapper, {
            std::any(_allocator)
          , [] (const std::any& allocator, const image_storage& image) -> void {
                VmaAllocator  memory_allocator = std::any_cast<VmaAllocator>(allocator);
                auto memory_allocation = std::any_cast<VmaAllocation>(image.image_allocation());
                vmaDestroyImage(memory_allocator, image.image(), memory_allocation);
            }
        });
    }

    vk::Sampler logical_device::create_sampler(const gsl::not_null<sampler_state*> state) const noexcept
    {
        auto create_info = vk::SamplerCreateInfo();

//        /// Gets or sets the texture-address mode for the u-coordinate.
//        texture_address_mode address_u { texture_address_mode::wrap };

//        /// Gets or sets the texture-address mode for the v-coordinate.
//        texture_address_mode address_v { texture_address_mode::wrap };

//        /// Gets or sets the texture-address mode for the w-coordinate.
//        texture_address_mode address_w { texture_address_mode::wrap };

//        /// Gets or sets the type of filtering during sampling.
//        texture_filter mag_filter { texture_filter::linear };

//        /// Gets or sets the type of filtering during sampling.
//        texture_filter min_filter { texture_filter::linear };

//        /// Gets or sets the maximum anisotropy. The default value is 0.
//        std::int32_t max_anisotropy { 4 };

//        /// Gets or sets the level of detail (LOD) index of the largest map to use.
//        std::size_t max_mip_level { 0 };

//        /// Gets or sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
//        float mip_map_level_of_detail_bias { 0 };

        vk::Sampler sampler;

        auto result = _logical_device.createSampler(&create_info, nullptr, &sampler);

        check_result(result);

        return sampler;
    }

    void logical_device::create_allocator(const vk::PhysicalDevice& physical_device
                                        , const vk::Device&         logical_device) noexcept
    {
        VmaAllocatorCreateInfo allocatorInfo = { };
        allocatorInfo.physicalDevice = physical_device;
        allocatorInfo.device         = logical_device;

        auto result = vmaCreateAllocator(&allocatorInfo, &_allocator);

        Ensures(result == VK_SUCCESS);
    }

    void logical_device::get_device_queues() noexcept
    {
        _logical_device.getQueue(_graphics_queue_family_index, 0, &_graphics_queue);
        _logical_device.getQueue(_present_queue_family_index, 0, &_present_queue);
    }

    void logical_device::begin_single_time_commands() noexcept
    {
        auto begin_info = vk::CommandBufferBeginInfo()
            .setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        reset_fence(_single_time_command_fence);

        auto result = _single_time_command_buffer.begin(&begin_info);

        check_result(result);
    }

    void logical_device::end_single_time_commands() noexcept
    {
        _single_time_command_buffer.end();

        auto submit_info = vk::SubmitInfo()
            .setCommandBufferCount(1)
            .setPCommandBuffers(&_single_time_command_buffer);

        auto result = _graphics_queue.submit(1, &submit_info, _single_time_command_fence);

        check_result(result);

        _graphics_queue.waitIdle();
    }

    void logical_device::reset_fence(const vk::Fence& fence) const noexcept
    {
        check_result(_logical_device.waitForFences(fence, VK_TRUE, UINT64_MAX));
        check_result(_logical_device.resetFences(1, &fence));
    }

    void logical_device::create_sync_primitives() noexcept
    {
        const auto semaphore_create_info = vk::SemaphoreCreateInfo();
        const auto fence_create_info     = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);

        _fences.resize(_surface_capabilities.minImageCount);
        _image_acquired_semaphores.resize(_surface_capabilities.minImageCount);
        _draw_complete_semaphores.resize(_surface_capabilities.minImageCount);
        _image_ownership_semaphores.resize(_surface_capabilities.minImageCount);

        auto result = _logical_device.createFence(&fence_create_info, nullptr, &_single_time_command_fence);
        check_result(result);

        for (std::uint32_t i = 0; i < _surface_capabilities.minImageCount; ++i)
        {
            // Create fences that we can use to throttle if we get too far
            // ahead of the image presents
            result = _logical_device.createFence(&fence_create_info, nullptr, &_fences[i]);
            check_result(result);

            // Create semaphores to synchronize acquiring presentable buffers before
            // rendering and waiting for drawing to be complete before presenting
            result = _logical_device.createSemaphore(&semaphore_create_info, nullptr, &_image_acquired_semaphores[i]);
            check_result(result);

            result = _logical_device.createSemaphore(&semaphore_create_info, nullptr, &_draw_complete_semaphores[i]);
            check_result(result);

            result = _logical_device.createSemaphore(&semaphore_create_info, nullptr, &_image_ownership_semaphores[i]);
            check_result(result);
        }
    }

    void logical_device::create_command_pools() noexcept
    {
        // Main command pool
        auto create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_graphics_queue_family_index)
            .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        auto result = _logical_device.createCommandPool(&create_info, nullptr, &_command_pool);

        check_result(result);

        // Command pool for single time commands
        auto st_create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_graphics_queue_family_index)
            .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        result = _logical_device.createCommandPool(&st_create_info, nullptr, &_single_time_command_pool);

        check_result(result);
    }

    void logical_device::create_command_buffers() noexcept
    {
        // Main command buffers
        auto allocate_info = vk::CommandBufferAllocateInfo()
            .setCommandPool(_command_pool)
            .setCommandBufferCount(_surface_capabilities.minImageCount)
            .setLevel(vk::CommandBufferLevel::ePrimary);

        _command_buffers.resize(_surface_capabilities.minImageCount);

        auto result = _logical_device.allocateCommandBuffers(&allocate_info, _command_buffers.data());

        check_result(result);

        // Command buffers for single time commands
        auto st_allocate_info = vk::CommandBufferAllocateInfo()
            .setCommandPool(_single_time_command_pool)
            .setCommandBufferCount(1)
            .setLevel(vk::CommandBufferLevel::ePrimary);

        result = _logical_device.allocateCommandBuffers(&st_allocate_info, &_single_time_command_buffer);

        check_result(result);
    }

    void logical_device::create_render_pass() noexcept
    {
        std::vector<vk::AttachmentDescription> attachments;

        // For the color attachment, we'll simply be using the swapchain images.
        auto color_attachment = vk::AttachmentDescription()
            .setFormat(_surface_format.format)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStoreOp(vk::AttachmentStoreOp::eStore)
            .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
            .setInitialLayout(vk::ImageLayout::eUndefined)
            .setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

        attachments.push_back(color_attachment);

        // For the depth attachment, we'll be using the device depth format.
        auto depth_attachment = vk::AttachmentDescription()
            .setFormat(_depth_format)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStoreOp(vk::AttachmentStoreOp::eStore)
            .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
            .setInitialLayout(vk::ImageLayout::eUndefined)
            .setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        attachments.push_back(depth_attachment);

        // Now we enumerate the attachments for a subpass.  We have to have at least one subpass.
        auto color_ref = vk::AttachmentReference()
            .setAttachment(0)
            .setLayout(vk::ImageLayout::eColorAttachmentOptimal);

        auto depth_ref = vk::AttachmentReference()
            .setAttachment(1)
            .setLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        // Basically is this graphics or compute
        auto subpass = vk::SubpassDescription()
            .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
            .setColorAttachmentCount(1)
            .setPColorAttachments(&color_ref)
            .setPDepthStencilAttachment(&depth_ref);

        auto render_pass_create_info = vk::RenderPassCreateInfo()
            .setAttachmentCount(attachments.size())
            .setPAttachments(attachments.data())
            .setSubpassCount(1)
            .setPSubpasses(&subpass)
            .setDependencyCount(0);

        auto result = _logical_device.createRenderPass(&render_pass_create_info, nullptr, &_render_pass);

        check_result(result);
    }

    void logical_device::create_depth_buffer(vk::Extent2D extent) noexcept
    {
        image_options options;

        options.usage      = vk::ImageUsageFlagBits::eDepthStencilAttachment;
        options.extent     = vk::Extent3D(extent.width, extent.height, 1);
        options.mip_levels = 1;

        _depth_buffer = create_image(options);
    }

    void logical_device::create_frame_buffers(vk::Extent2D extent) noexcept
    {
        destroy_frame_buffers();

        _frame_buffers.reserve(_swap_chain_image_views.size());

        std::vector<vk::ImageView> attachments;

        attachments.reserve(2);

        attachments[1] = _depth_buffer->image_view();

        std::for_each(_swap_chain_image_views.begin(), _swap_chain_image_views.end(), [&] (const vk::ImageView& view) -> void
        {
            attachments[0] = view;

            auto create_info = vk::FramebufferCreateInfo()
                .setRenderPass(_render_pass)
                .setWidth(extent.width)
                .setHeight(extent.height)
                .setAttachmentCount(2)
                .setPAttachments(attachments.data())
                .setLayers(1);

            vk::Framebuffer buffer;

            auto result = _logical_device.createFramebuffer(&create_info, nullptr, &buffer);

            check_result(result);

            _frame_buffers.push_back(buffer);
        });
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
              , vk::DependencyFlagBits::eViewLocal
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
              , vk::DependencyFlagBits::eViewLocal
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

    void logical_device::destroy_sync_primitives() noexcept
    {
        _logical_device.waitIdle();

        _logical_device.waitForFences(1, &_single_time_command_fence, VK_TRUE, UINT64_MAX);
        _logical_device.destroyFence(_single_time_command_fence, nullptr);

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

    void logical_device::destroy_command_buffers() noexcept
    {
        // Main command buffers
        if (_command_buffers.size() > 0)
        {
            _logical_device.freeCommandBuffers(_command_pool, _surface_capabilities.minImageCount, _command_buffers.data());
        }
        _command_buffers.clear();

        // Single time command buffers
        _logical_device.freeCommandBuffers(_single_time_command_pool, 1, &_single_time_command_buffer);
    }

    void logical_device::destroy_command_pools() noexcept
    {
        // Main command pool
        _logical_device.destroyCommandPool(_command_pool, nullptr);

        // Single time commands command pool
        _logical_device.destroyCommandPool(_single_time_command_pool, nullptr);
    }

    void logical_device::destroy_swapchain_views() noexcept
    {
        std::for_each(_swap_chain_image_views.begin(), _swap_chain_image_views.end(), [&] (const auto& view) -> void {
            _logical_device.destroyImageView(view, nullptr);
        });

        _swap_chain_image_views.clear();
    }

    void logical_device::destroy_frame_buffers() noexcept
    {
        // Frame buffers
        std::for_each(_frame_buffers.begin(), _frame_buffers.end(), [&] (const auto& buffer) -> void {
            _logical_device.destroyFramebuffer(buffer, nullptr);
        });

        _frame_buffers.clear();
    }

    void logical_device::destroy_swap_chain() noexcept
    {
        // Sync primitives
        destroy_sync_primitives();

        // Frame buffers
        destroy_frame_buffers();

        // Render pass
        _logical_device.destroyRenderPass(_render_pass, nullptr);

        // Swapchain images
        _swap_chain_images.clear(); // swap chain images are destroyed by the vulkan driver

        // Swapchain image views
        destroy_swapchain_views();

        // Swapchains
        _logical_device.destroySwapchainKHR(_swap_chain, nullptr);
    }

    vk::PipelineColorBlendStateCreateInfo logical_device::vk_color_blend_state(
        const graphics::blend_state&           state
      , vk::PipelineColorBlendAttachmentState& attachment) const noexcept
    {
        auto enabled = !(state.color_source_blend      == graphics::blend::one
                      && state.color_destination_blend == graphics::blend::zero
                      && state.alpha_source_blend      == graphics::blend::one
                      && state.alpha_destination_blend == graphics::blend::zero);

        attachment
            .setBlendEnable(enabled)
            .setColorWriteMask(static_cast<vk::ColorComponentFlagBits>(state.color_write_channels_1))
            .setAlphaBlendOp(static_cast<vk::BlendOp>(state.alpha_blend_function))
            .setSrcAlphaBlendFactor(static_cast<vk::BlendFactor>(state.alpha_source_blend))
            .setDstAlphaBlendFactor(static_cast<vk::BlendFactor>(state.alpha_destination_blend))
            .setColorBlendOp(static_cast<vk::BlendOp>(state.color_blend_function))
            .setSrcColorBlendFactor(static_cast<vk::BlendFactor>(state.color_source_blend))
            .setDstColorBlendFactor(static_cast<vk::BlendFactor>(state.color_destination_blend));

        auto create_info = vk::PipelineColorBlendStateCreateInfo()
            .setLogicOpEnable(false)
            .setLogicOp(vk::LogicOp::eCopy)
            .setAttachmentCount(1)
            .setPAttachments(&attachment)
            .setBlendConstants({
                state.blend_factor.r / 255
              , state.blend_factor.g / 255
              , state.blend_factor.b / 255
              , state.blend_factor.a / 255
             });

        return create_info;
    }

    vk::PipelineDepthStencilStateCreateInfo logical_device::vk_depth_stencil_state(const graphics::depth_stencil_state& state) const noexcept
    {
        auto create_info = vk::PipelineDepthStencilStateCreateInfo()
            // depth
            .setDepthTestEnable(state.depth_buffer_enable)
            .setDepthWriteEnable(state.depth_buffer_write_enable)
            .setDepthCompareOp(static_cast<vk::CompareOp>(state.depth_buffer_function))
            .setMinDepthBounds(0.0f)
            .setMaxDepthBounds(1.0f)
            // stencil
            .setStencilTestEnable(state.stencil_enable);

        create_info
            .setFront(
                vk::StencilOpState()
                    .setFailOp(static_cast<vk::StencilOp>(state.stencil_fail))
                    .setPassOp(static_cast<vk::StencilOp>(state.stencil_pass))
                    .setDepthFailOp(static_cast<vk::StencilOp>(state.stencil_depth_buffer_fail))
                    .setCompareOp(static_cast<vk::CompareOp>(state.stencil_function))
                    .setCompareMask(state.stencil_mask)
                    .setWriteMask(state.stencil_write_mask)
                    .setReference(state.reference_stencil)
             );

        if (state.two_sided_stencil_mode)
        {
            create_info
                .setBack(
                    vk::StencilOpState()
                        .setFailOp(static_cast<vk::StencilOp>(state.counter_clockwise_stencil_fail))
                        .setPassOp(static_cast<vk::StencilOp>(state.counter_clockwise_stencil_pass))
                        .setDepthFailOp(static_cast<vk::StencilOp>(state.counter_clockwise_stencil_depth_buffer_fail))
                        .setCompareOp(static_cast<vk::CompareOp>(state.counter_clockwise_stencil_function))
                        .setCompareMask(state.stencil_mask)
                        .setWriteMask(state.stencil_write_mask)
                        .setReference(state.reference_stencil)
                 );
        }

        return create_info;
    }

    vk::PipelineRasterizationStateCreateInfo logical_device::vk_rasterizer_state(const graphics::rasterizer_state& state) const noexcept
    {
        auto create_info = vk::PipelineRasterizationStateCreateInfo()
             // If rasterizerDiscardEnable is set to true, then geometry never passes through the rasterizer stage.
            .setRasterizerDiscardEnable(false)
            .setPolygonMode(static_cast<vk::PolygonMode>(state.fill_mode))
            .setLineWidth(1.0f)
            .setDepthBiasClamp(state.scissor_test_enable)
            .setDepthBiasEnable(state.depth_bias != 0.0f || state.slope_scale_depth_bias != 0.0f)
            .setDepthBiasClamp(state.depth_bias)
            .setDepthBiasConstantFactor(state.depth_bias)
            .setDepthBiasSlopeFactor(state.slope_scale_depth_bias);

        switch (state.cull_mode)
        {
        case graphics::cull_mode::cull_clockwise_face:
            create_info
                .setCullMode(vk::CullModeFlagBits::eFront)
                .setFrontFace(vk::FrontFace::eClockwise);
            break;

        case graphics::cull_mode::cull_counter_clockwise_face:
            create_info
                .setCullMode(vk::CullModeFlagBits::eBack)
                .setFrontFace(vk::FrontFace::eCounterClockwise);
            break;

        case graphics::cull_mode::none:
            create_info
                .setCullMode(vk::CullModeFlagBits::eFrontAndBack)
                .setFrontFace(vk::FrontFace::eCounterClockwise);
            break;
        }

        return create_info;
    }
}
