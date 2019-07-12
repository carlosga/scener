// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/logical_device.hpp"

#include <string>
#include <gsl/gsl>

#include "scener/graphics/constant_buffer.hpp"
#include "scener/graphics/effect_parameter.hpp"
#include "scener/graphics/effect_pass.hpp"
#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/fill_mode.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/texture2d.hpp"
#include "scener/graphics/texture_address_mode.hpp"
#include "scener/graphics/texture_filter.hpp"
#include "scener/graphics/vertex_element_format.hpp"
#include "scener/graphics/vertex_buffer.hpp"
#include "scener/graphics/vulkan/shader.hpp"
#include "scener/graphics/vulkan/shader_module.hpp"
#include "scener/graphics/vulkan/shader_stage.hpp"
#include "scener/graphics/vulkan/surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"
#include "scener/math/basic_rect.hpp"

namespace scener::graphics::vulkan
{
    using scener::graphics::vertex_element_format;
    using scener::graphics::viewport;
    using scener::math::basic_color;

    vk::SamplerAddressMode logical_device::vkSamplerAddressMode(const scener::graphics::texture_address_mode& address_mode) noexcept
    {
        switch (address_mode)
        {
        case scener::graphics::texture_address_mode::wrap:
            return vk::SamplerAddressMode::eRepeat;
        case scener::graphics::texture_address_mode::clamp:
            return vk::SamplerAddressMode::eClampToEdge;
        case scener::graphics::texture_address_mode::mirror:
            return vk::SamplerAddressMode::eMirroredRepeat;
        }
    }

    vk::Filter logical_device::vkFilter(const scener::graphics::texture_filter& filter) noexcept
    {
        switch (filter)
        {
        case scener::graphics::texture_filter::linear:
            return vk::Filter::eLinear;
        case scener::graphics::texture_filter::linear_mipmap_point:
            return vk::Filter::eNearest;
        default:
            return vk::Filter::eLinear;
        }
    }

    vk::Format logical_device::vkFormat(const scener::graphics::vertex_element_format& format) noexcept
    {
        switch (format)
        {
        case scener::graphics::vertex_element_format::single:
            return vk::Format::eR32Sfloat;
        case scener::graphics::vertex_element_format::vector2:
            return vk::Format::eR32G32Sfloat;
        case scener::graphics::vertex_element_format::vector3:
            return vk::Format::eR32G32B32Sfloat;
        case scener::graphics::vertex_element_format::vector4:
            return vk::Format::eR32G32B32A32Sfloat;
        case scener::graphics::vertex_element_format::color:
            return vk::Format::eR32G32B32A32Sfloat;
        case scener::graphics::vertex_element_format::byte4:
            return vk::Format::eR8Srgb;
        case scener::graphics::vertex_element_format::short2:
            return vk::Format::eR16G16Sint;
        case scener::graphics::vertex_element_format::short4:
            return vk::Format::eR16G16B16A16Sint;
        }
    }

    vk::Format logical_device::vkFormat(const scener::graphics::surface_format& format) noexcept
    {
        switch (format)
        {
        case scener::graphics::surface_format::color:
            return vk::Format::eR8Srgb;
        case scener::graphics::surface_format::bgr565:
            return vk::Format::eR5G6B5UnormPack16;
        case scener::graphics::surface_format::bgra5551:
            return vk::Format::eR5G5B5A1UnormPack16;
        case scener::graphics::surface_format::bgra4444:
            return vk::Format::eR4G4B4A4UnormPack16;
        case scener::graphics::surface_format::dxt1:
            return vk::Format::eBc1RgbaUnormBlock;
        case scener::graphics::surface_format::dxt3:
            return vk::Format::eBc3UnormBlock;
        case scener::graphics::surface_format::dxt5:
            return vk::Format::eBc5UnormBlock;
        case scener::graphics::surface_format::normalized_byte2:
            return vk::Format::eR8G8Snorm;
        case scener::graphics::surface_format::normalized_byte4:
            return vk::Format::eR8G8B8Snorm;
        case scener::graphics::surface_format::rg32:
            return vk::Format::eR16G16Uint;
        case scener::graphics::surface_format::rgba64: ///< 64-bit RGBA pixel format using 16 bits for each component.
            return vk::Format::eR16G16B16A16Uint;
        }
    }

    logical_device::logical_device(const vk::PhysicalDevice&         physical_device
                                 , const vk::Device&                 logical_device
                                 , const viewport&                   viewport
                                 , std::uint32_t                     graphics_queue_family_index
                                 , std::uint32_t                     present_queue_family_index
                                 , const vk::SurfaceCapabilitiesKHR& surface_capabilities
                                 , const vk::SurfaceFormatKHR&       surface_format
                                 , const vk::Format&                 depth_format
                                 , const vk::PresentModeKHR&         present_mode
                                 , const vk::FormatProperties&       format_properties) noexcept
        : _logical_device                   { logical_device }
        , _viewport                         { }
        , _graphics_queue_family_index      { graphics_queue_family_index }
        , _graphics_queue                   { }
        , _present_queue_family_index       { present_queue_family_index }
        , _present_queue                    { }
        , _surface_capabilities             { surface_capabilities }
        , _surface_format                   { surface_format }
        , _present_mode                     { present_mode }
        , _format_properties                { format_properties }
        , _command_pool                     { }
        , _single_time_command_pool         { }
        , _swap_chain                       { }
        , _render_pass                      { }
        , _swap_chain_images                { }
        , _swap_chain_image_views           { }
        , _frame_buffers                    { }
        , _command_buffers                  { }
        , _single_time_command_buffer       { }
        , _fences                           { }
        , _single_time_command_fence        { }
        , _image_acquired_semaphores        { }
        , _draw_complete_semaphores         { }
        , _image_ownership_semaphores       { }
        , _frame_index                      { 0 }
        , _depth_format                     { depth_format }
        , _depth_buffer                     { }
        , _pipeline_cache                   { }
        , _allocator                        { }
    {
        create_viewport(viewport);
        create_allocator(physical_device, logical_device);
        get_device_queues();
        create_command_pools();
        create_sync_primitives();
        create_pipeline_cache();
    }

    logical_device::~logical_device() noexcept
    {
        // Swapchain
        destroy_swap_chain();

        // Command buffers
        destroy_command_buffers();

        // Command pools
        destroy_command_pools();

        // Depth buffer
        _depth_buffer.destroy();

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

    void logical_device::draw() noexcept
    {
        std::uint32_t current_buffer = 0;

        // Acquire swapchain image
        auto result = _logical_device.acquireNextImageKHR(
            _swap_chain
          , std::numeric_limits<std::uint64_t>().max()
          , _image_acquired_semaphores[_frame_index]
          , vk::Fence()
          , &current_buffer);

        check_result(result);

        reset_fence(_fences[_frame_index]);

        // Submit command buffer
        static const vk::PipelineStageFlags pipe_stage_flags = vk::PipelineStageFlagBits::eColorAttachmentOutput;

        auto submit_info = vk::SubmitInfo()
            .setPWaitDstStageMask(&pipe_stage_flags)
            .setWaitSemaphoreCount(1)
            .setPWaitSemaphores(&_image_acquired_semaphores[_frame_index])
            .setCommandBufferCount(1)
            .setPCommandBuffers(&_command_buffers[current_buffer])
            .setSignalSemaphoreCount(1)
            .setPSignalSemaphores(&_draw_complete_semaphores[_frame_index]);

        result = _graphics_queue.submit(1, &submit_info, _fences[_frame_index]);

        check_result(result);

        const auto separate_present_queue = _graphics_queue_family_index != _present_queue_family_index;

        auto present_info = vk::PresentInfoKHR()
            .setWaitSemaphoreCount(1)
            .setPWaitSemaphores(separate_present_queue ? &_image_ownership_semaphores[_frame_index]
                                                       : &_draw_complete_semaphores[_frame_index])
            .setSwapchainCount(1)
            .setPSwapchains(&_swap_chain)
            .setPImageIndices(&current_buffer);

        result = _graphics_queue.presentKHR(&present_info);

        check_result(result);

        _frame_index += 1;
        _frame_index %= 2;
    }

    void logical_device::present() noexcept
    {
    }

    void logical_device::begin_prepare() noexcept
    {
        for (std::uint32_t current_buffer = 0; current_buffer < _swap_chain_images.size(); ++current_buffer)
        {
            auto image_subresource_range = vk::ImageSubresourceRange()
                 .setAspectMask(vk::ImageAspectFlagBits::eColor)
                 .setBaseMipLevel(0)
                 .setLevelCount(1)
                 .setBaseArrayLayer(0)
                 .setLayerCount(1);

            const auto& command_buffer           = _command_buffers[current_buffer];
            const auto command_buffer_begin_info = vk::CommandBufferBeginInfo()
                .setFlags(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

            // Begin main command buffer
            auto result = command_buffer.begin(&command_buffer_begin_info);

            check_result(result);

            static const vk::ClearValue clear_values[2] =
            {
                vk::ClearColorValue(std::array<float, 4>({ { 0, 0, 0, 1.0f } })),
                vk::ClearDepthStencilValue(1.0f, 0u)
            };

            // Begin render pass
            const auto render_area = vk::Rect2D()
                .setOffset({ static_cast<std::int32_t>(_viewport.x)
                           , static_cast<std::int32_t>(_viewport.y) })
                .setExtent({ static_cast<std::uint32_t>(_viewport.width)
                           , static_cast<std::uint32_t>(_viewport.height) });

            const auto render_pass_begin_info = vk::RenderPassBeginInfo()
                .setRenderPass(_render_pass)
                .setFramebuffer(_frame_buffers[current_buffer])
                .setRenderArea(render_area)
                .setClearValueCount(2)
                .setPClearValues(clear_values);

            command_buffer.beginRenderPass(&render_pass_begin_info, vk::SubpassContents::eInline);

            // Set the viewport
            command_buffer.setViewport(0, 1, &_viewport);

            // Set scissor
            vk::Rect2D const scissor(vk::Offset2D(static_cast<std::int32_t>(_viewport.x)     , static_cast<std::int32_t>(_viewport.y))
                                   , vk::Extent2D(static_cast<std::uint32_t>(_viewport.width), static_cast<std::uint32_t>(_viewport.height)));

            command_buffer.setScissor(0, 1, &scissor);
        }
    }

    void logical_device::bind_graphics_pipeline(const graphics_pipeline& pipeline) const noexcept
    {
        for (std::uint32_t current_buffer = 0; current_buffer < _swap_chain_images.size(); ++current_buffer)
        {
            _command_buffers[current_buffer].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.pipeline());
            _command_buffers[current_buffer].bindDescriptorSets(
                vk::PipelineBindPoint::eGraphics
              , pipeline.pipeline_layout()
              , 0
              , 1
              , &pipeline.descriptors()[current_buffer]
              , 0
              , nullptr);
        }
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
        static const vk::DeviceSize offsets[] = { 0 };

        const auto index_element_type = static_cast<vk::IndexType>(index_buffer->index_element_type());
        const auto offset             = start_index * index_buffer->element_size_in_bytes();

        for (std::uint32_t current_buffer = 0; current_buffer < _swap_chain_images.size(); ++current_buffer)
        {
            const auto& command_buffer = _command_buffers[current_buffer];

            // Vertex buffer binding
            command_buffer.bindVertexBuffers(0, 1, &vertex_buffer->_buffer.resources(0).memory_buffer, offsets);

            // Index buffer binding
            command_buffer.bindIndexBuffer(index_buffer->_buffer.resources(0).memory_buffer, 0, index_element_type);

            // Draw call
            command_buffer.drawIndexed(
                index_buffer->index_count()
              , 1
              , start_index
              , offset
              , base_vertex);
        }
    }

    void logical_device::end_prepare() noexcept
    {
        for (std::uint32_t current_buffer = 0; current_buffer < _swap_chain_images.size(); ++current_buffer)
        {
            _command_buffers[current_buffer].endRenderPass();
            _command_buffers[current_buffer].end();
        }
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

                _single_time_command_buffer.copyBuffer(staging_buffer, buffer_instance.resources(0).memory_buffer, 1, &buffer_copy_region);

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
        vk::ImageUsageFlags image_usage = vk::ImageUsageFlagBits::eColorAttachment;
        if (_surface_capabilities.supportedUsageFlags & vk::ImageUsageFlagBits::eTransferDst)
        {
            image_usage |= vk::ImageUsageFlagBits::eTransferDst;
        }

        vk::SurfaceTransformFlagBitsKHR pre_transform;
        if (_surface_capabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
        {
            pre_transform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
        }
        else
        {
            pre_transform = _surface_capabilities.currentTransform;
        }

        // Find a supported composite alpha mode - one of these is guaranteed to be set
        vk::CompositeAlphaFlagBitsKHR composite_alpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
        vk::CompositeAlphaFlagBitsKHR composite_alpha_flags[4] = {
            vk::CompositeAlphaFlagBitsKHR::eOpaque,
            vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
            vk::CompositeAlphaFlagBitsKHR::ePostMultiplied,
            vk::CompositeAlphaFlagBitsKHR::eInherit,
        };
        for (uint32_t i = 0; i < 4; i++)
        {
            if (_surface_capabilities.supportedCompositeAlpha & composite_alpha_flags[i])
            {
                composite_alpha = composite_alpha_flags[i];
                break;
            }
        }

        // https://www.fasterthan.life/blog/2017/7/12/i-am-graphics-and-so-can-you-part-3-breaking-ground
        const std::uint32_t queue_indices[2] = { _graphics_queue_family_index, _present_queue_family_index };
        const auto extent = surface.extent(_surface_capabilities);

        auto chain_info = vk::SwapchainCreateInfoKHR()
            .setSurface(surface.surface())
            .setMinImageCount(_surface_capabilities.minImageCount)
            .setImageFormat(_surface_format.format)
            .setImageColorSpace(_surface_format.colorSpace)
            .setImageExtent(extent)
            .setImageArrayLayers(1)
            .setImageUsage(image_usage)
            .setImageSharingMode(vk::SharingMode::eExclusive)
            .setQueueFamilyIndexCount(0)
            .setPQueueFamilyIndices(nullptr)
            .setPreTransform(pre_transform)
            .setCompositeAlpha(composite_alpha)
            .setPresentMode(_present_mode)
            .setClipped(true);

        // If the graphics queue family and present family don't match then we need to create the
        // swapchain with different information.
        if (_graphics_queue_family_index != _present_queue_family_index)
        {
            // There are only two sharing modes.  This is the one to use
            // if images are not exclusive to one queue.
            chain_info
                .setImageSharingMode(vk::SharingMode::eConcurrent)
                .setQueueFamilyIndexCount(2)
                .setPQueueFamilyIndices(queue_indices);
        }

        auto result = _logical_device.createSwapchainKHR(&chain_info, nullptr, &_swap_chain);

        check_result(result);

        // Retrieve the swapchain images from the device.
        // Note that VkImage is simply a handle like everything else.

        // First call gets numImages.
        std::uint32_t num_images = 0;

        result = _logical_device.getSwapchainImagesKHR(_swap_chain, &num_images, static_cast<vk::Image *>(nullptr));

        check_result(result);
        Ensures(num_images > 0);

        _swap_chain_images.resize(num_images);

        result = _logical_device.getSwapchainImagesKHR(_swap_chain, &num_images, _swap_chain_images.data());

        check_result(result);

        // Image Views
        create_image_views();

        // Command buffers
        create_command_buffers();

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

    graphics_pipeline logical_device::create_graphics_pipeline(
          const graphics::blend_state&         color_blend_state
        , const graphics::depth_stencil_state& depth_stencil_state
        , const graphics::rasterizer_state&    rasterization_state
        , const graphics::model_mesh_part&     model_mesh_part) const noexcept
    {
        const auto scissor = vk::Rect2D()
            .setOffset({ static_cast<std::int32_t>(_viewport.x)
                       , static_cast<std::int32_t>(_viewport.y) })
            .setExtent({ static_cast<std::uint32_t>(_viewport.width)
                       , static_cast<std::uint32_t>(_viewport.height) });

        const auto viewport_state = vk::PipelineViewportStateCreateInfo()
            .setViewportCount(1)
            .setPViewports(&_viewport)
            .setScissorCount(1)
            .setPScissors(&scissor);

        // Color blend, depth stencil and rasterier states
        auto color_blend_attachment = vk::PipelineColorBlendAttachmentState();

        const auto color_blend_state_info   = vk_color_blend_state(color_blend_state, color_blend_attachment);
        const auto depth_stencil_state_info = vk_depth_stencil_state(depth_stencil_state);
        const auto rasterizer_state_info    = vk_rasterizer_state(rasterization_state);

        // Multisampling state
        const auto multisampling_state_info = vk::PipelineMultisampleStateCreateInfo()
            .setSampleShadingEnable(rasterization_state.multi_sample_anti_alias)
            .setRasterizationSamples(vk::SampleCountFlagBits::e1)
            .setMinSampleShading(1.0f)
            .setPSampleMask(nullptr)
            .setAlphaToCoverageEnable(false)
            .setAlphaToOneEnable(false);

        // Dynamic states
        const vk::DynamicState dynamic_states[] = { vk::DynamicState::eViewport , vk::DynamicState::eScissor };

        const auto dynamic_states_info = vk::PipelineDynamicStateCreateInfo()
            .setDynamicStateCount(2)
            .setPDynamicStates(dynamic_states);

        // Assembly state
        const auto input_assembly_state = vk::PipelineInputAssemblyStateCreateInfo()
            .setTopology(static_cast<vk::PrimitiveTopology>(model_mesh_part.primitive_type()));

        // Shader stages
        const auto effect_pass = model_mesh_part.effect_technique()->passes().at(0);

        std::vector<vk::ShaderModule>                  shader_modules;
        std::vector<vk::PipelineShaderStageCreateInfo> shader_stages_create_infos;

        for (const auto& shader : effect_pass->shader_module()->shaders())
        {
            auto create_info = vk::ShaderModuleCreateInfo()
                .setCodeSize(shader->buffer().size())
                .setPCode(reinterpret_cast<const std::uint32_t*>(shader->buffer().data()));

            auto shader_module = _logical_device.createShaderModule(create_info, nullptr);

            shader_modules.push_back(shader_module);

            const auto stageFlags = static_cast<vk::ShaderStageFlagBits>(shader->stage());

            auto stage = vk::PipelineShaderStageCreateInfo()
                .setModule(shader_module)
                .setStage(stageFlags)
                .setPName(shader->entry_point().c_str());

            shader_stages_create_infos.push_back(stage);
        }

        // Vertex buffer
        const auto& vertex_declaration = model_mesh_part.vertex_buffer()->vertex_declaration();
        const auto vertexInputBinding  = vk::VertexInputBindingDescription()
            .setBinding(0)
            .setStride(vertex_declaration.vertex_stride())
            .setInputRate(vk::VertexInputRate::eVertex);

        std::vector<vk::VertexInputAttributeDescription> vertexAttributes;

        vertexAttributes.reserve(vertex_declaration.vertex_elements().size());

        std::for_each(vertex_declaration.vertex_elements().begin()
                    , vertex_declaration.vertex_elements().end()
                    , [&] (const auto& element) {
                        auto attr = vk::VertexInputAttributeDescription()
                            .setBinding(0)
                            .setLocation(element.usage_index())
                            .setOffset(element.offset())
                            .setFormat(vkFormat(element.format()));

                        vertexAttributes.push_back(attr);
                      });

        const auto vertex_input_state = vk::PipelineVertexInputStateCreateInfo()
            .setPVertexBindingDescriptions(&vertexInputBinding)
            .setVertexBindingDescriptionCount(1)
            .setPVertexAttributeDescriptions(vertexAttributes.data())
            .setVertexAttributeDescriptionCount(static_cast<std::uint32_t>(vertexAttributes.size()));

        // Descriptor pool
        const auto& textures          = model_mesh_part.effect_technique()->textures();
        const auto  texture_count     = static_cast<std::uint32_t>(textures.size());
        const auto  descriptor_pool   = create_descriptor_pool(texture_count);
        const auto  descriptor_layout = create_descriptor_layout(texture_count);
        const auto  pipeline_layout   = create_pipeline_layout(descriptor_layout);

        // Graphics pipeline
        const auto pipeline_create_info = vk::GraphicsPipelineCreateInfo()
            .setStageCount(static_cast<std::uint32_t>(shader_stages_create_infos.size()))
            .setPStages(shader_stages_create_infos.data())
            .setPVertexInputState(&vertex_input_state)
            .setPInputAssemblyState(&input_assembly_state)
            .setPViewportState(&viewport_state)
            .setPRasterizationState(&rasterizer_state_info)
            .setPMultisampleState(&multisampling_state_info)
            .setPDepthStencilState(&depth_stencil_state_info)
            .setPColorBlendState(&color_blend_state_info)
            .setPDynamicState(&dynamic_states_info)
            .setLayout(pipeline_layout)
            .setRenderPass(_render_pass);

        // Graphics pipeline initialization
        vk::Pipeline pipeline;

        auto result = _logical_device.createGraphicsPipelines(_pipeline_cache, 1, &pipeline_create_info, nullptr, &pipeline);

        check_result(result);

        // Destroy the shader modules
        std::for_each(shader_modules.begin(), shader_modules.end(), [&] (auto& module) {
            _logical_device.destroyShaderModule(module, nullptr);
        });

        // Descriptors
        const auto constant_buffer = effect_pass->constant_buffer();
        auto buffer_info           = vk::DescriptorBufferInfo()
            .setOffset(0)
            .setRange(constant_buffer->size());

        vk::DescriptorImageInfo tex_descs[texture_count];

        for (std::uint32_t i = 0; i < texture_count; i++)
        {
            tex_descs[i].setSampler(textures[i]->sampler());
            tex_descs[i].setImageView(textures[i]->view());
            tex_descs[i].setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
        }

        vk::WriteDescriptorSet writes[2];

        writes[0].setDstBinding(0);
        writes[0].setDescriptorCount(1);
        writes[0].setDescriptorType(vk::DescriptorType::eUniformBuffer);
        writes[0].setPBufferInfo(&buffer_info);

        writes[1].setDstBinding(1);
        writes[1].setDescriptorCount(texture_count);
        writes[1].setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        writes[1].setPImageInfo(tex_descs);

        const auto descriptor_set_alloc_info = vk::DescriptorSetAllocateInfo()
            .setDescriptorPool(descriptor_pool)
            .setDescriptorSetCount(1)
            .setPSetLayouts(&descriptor_layout);

        std::vector<vk::DescriptorSet> descriptors(2);

        for (std::uint32_t i = 0; i < _swap_chain_images.size(); ++i)
        {
            auto result = _logical_device.allocateDescriptorSets(&descriptor_set_alloc_info, &descriptors[i]);

            check_result(result);

            buffer_info.setBuffer(constant_buffer->memory_buffer().resources(i).memory_buffer);
            writes[0].setDstSet(descriptors[i]);
            writes[1].setDstSet(descriptors[i]);

            _logical_device.updateDescriptorSets(2, writes, 0, nullptr);
        }

        return { pipeline, pipeline_layout, descriptor_pool, descriptor_layout, descriptors };
    }

    vk::Sampler logical_device::create_sampler(gsl::not_null<const sampler_state*> sampler_state) const noexcept
    {
        auto create_info = vk::SamplerCreateInfo()
            .setCompareOp(vk::CompareOp::eLess)
            .setMipmapMode(vk::SamplerMipmapMode::eNearest)
            .setMinLod(0)
            .setMaxLod(sampler_state->max_mip_level)
            .setMipLodBias(sampler_state->mip_map_level_of_detail_bias)
            .setAddressModeU(vkSamplerAddressMode(sampler_state->address_u))
            .setAddressModeV(vkSamplerAddressMode(sampler_state->address_v))
            .setAddressModeW(vkSamplerAddressMode(sampler_state->address_w))
            .setMagFilter(vkFilter(sampler_state->mag_filter))
            .setMinFilter(vkFilter(sampler_state->min_filter))
            .setMaxAnisotropy(sampler_state->max_anisotropy)
            .setAnisotropyEnable(false);

        vk::Sampler sampler;

        auto result = _logical_device.createSampler(&create_info, nullptr, &sampler);

        check_result(result);

        return sampler;
    }

    texture_object logical_device::create_texture_object(gsl::not_null<const scener::content::dds::surface*>   source
                                                       , gsl::not_null<const scener::graphics::sampler_state*> sampler_state
                                                       , vk::ImageTiling                                       tiling
                                                       , vk::ImageUsageFlags                                   usage
                                                       , vk::MemoryPropertyFlags                               required_props) noexcept
    {
        texture_object texture;

        texture.width  = source->width();
        texture.height = source->height();

        // Create & allocate the image
        const auto format = vkFormat(source->format());
        const auto image_create_info = vk::ImageCreateInfo()
            .setImageType(vk::ImageType::e2D)
            .setFormat(format)
            .setExtent({ texture.width, texture.height, 1})
            // .setMipLevels(static_cast<std::uint32_t>(source.mipmaps().size()))
            .setMipLevels(1)
            .setArrayLayers(1)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setTiling(tiling)
            .setUsage(usage)
            .setSharingMode(vk::SharingMode::eExclusive)
            .setQueueFamilyIndexCount(0)
            .setPQueueFamilyIndices(nullptr)
            .setInitialLayout(vk::ImageLayout::ePreinitialized);

        VmaAllocationCreateInfo create_info = { };

        create_info.usage         = VMA_MEMORY_USAGE_GPU_ONLY;
        create_info.requiredFlags = static_cast<VkMemoryPropertyFlags>(required_props);

        auto create_image_result = vmaCreateImage(
            _allocator
          , reinterpret_cast<const VkImageCreateInfo*>(&image_create_info)
          , &create_info
          , reinterpret_cast<VkImage*>(&texture.image)
          , &texture.allocation
          , &texture.allocation_info);

        Ensures(create_image_result == VK_SUCCESS);

        // Copy the image contents to a staging buffer
        const auto& mipmap      = source->mipmap(0).view();
        const auto  mipmap_size = static_cast<std::uint32_t>(mipmap.size());

        VkBufferCreateInfo buffer_create_info = {
            VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO    // VkStructureType
          , nullptr                                 // pNext
          , 0                                       // flags
          , mipmap_size                             // size
          , VK_BUFFER_USAGE_TRANSFER_SRC_BIT        // usage
          , VK_SHARING_MODE_EXCLUSIVE               // sharingMode
          , 0                                       // queueFamilyIndexCount
          , nullptr                                 // pQueueFamilyIndices
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

        std::copy_n(mipmap.data(), mipmap.size(), reinterpret_cast<char*>(staging_buffer_alloc_info.pMappedData));

        // Layout transitions using barriers
        auto subresource_range = vk::ImageSubresourceRange()
            .setAspectMask(vk::ImageAspectFlagBits::eColor)
            .setBaseMipLevel(0)
            .setLevelCount(1)
            .setBaseArrayLayer(0)
            .setLayerCount(1);

        begin_single_time_commands();

        auto barrier = vk::ImageMemoryBarrier()
            .setOldLayout(vk::ImageLayout::eUndefined)
            .setNewLayout(vk::ImageLayout::eTransferDstOptimal)
            .setSrcQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
            .setDstQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
            .setImage(texture.image)
            .setSubresourceRange(subresource_range)
            .setSrcAccessMask(vk::AccessFlagBits())
            .setDstAccessMask(vk::AccessFlagBits::eTransferWrite);

        _single_time_command_buffer.pipelineBarrier(
            vk::PipelineStageFlagBits::eTopOfPipe
          , vk::PipelineStageFlagBits::eTransfer
          , vk::DependencyFlagBits()
          , 0, nullptr
          , 0, nullptr
          , 1, &barrier);

        // Copy the texture data using the staging buffer
        auto region = vk::BufferImageCopy()
            .setImageExtent({ texture.width, texture.height, 1 })
            .setImageSubresource({vk::ImageAspectFlagBits::eColor, 1 });

        _single_time_command_buffer.copyBufferToImage(
            staging_buffer
          , texture.image
          , vk::ImageLayout::eTransferDstOptimal
          , 1, &region);

        barrier
            .setOldLayout(vk::ImageLayout::eTransferDstOptimal)
            .setNewLayout(vk::ImageLayout::eShaderReadOnlyOptimal)
            .setImage(texture.image)
            .setSrcAccessMask(vk::AccessFlagBits::eTransferWrite)
            .setDstAccessMask(vk::AccessFlagBits::eShaderRead);

        _single_time_command_buffer.pipelineBarrier(
            vk::PipelineStageFlagBits::eTransfer
          , vk::PipelineStageFlagBits::eFragmentShader
          , vk::DependencyFlagBits()
          , 0, nullptr
          , 0, nullptr
          , 1, &barrier);

        end_single_time_commands();

        // Destroy the staging buffer
        vmaDestroyBuffer(_allocator, staging_buffer, staging_buffer_allocation);

        // Create Image View
        auto view_create_info = vk::ImageViewCreateInfo()
            .setImage(texture.image)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(format)
            .setSubresourceRange(subresource_range);

        check_result(_logical_device.createImageView(&view_create_info, nullptr, &texture.view));

        texture.sampler      = create_sampler(sampler_state);
        texture.image_layout = vk::ImageLayout::eShaderReadOnlyOptimal;
        texture.allocator    = &_allocator;

        return texture;
    }

    void logical_device::destroy(const texture_object& texture) const noexcept
    {
        _logical_device.destroySampler(texture.sampler, nullptr);
        vmaDestroyImage(_allocator, texture.image, texture.allocation);
    }

    void logical_device::create_viewport(const viewport& viewport)
    {
        _viewport
            .setX(viewport.rect.x())
            .setY(viewport.rect.y())
            .setWidth(viewport.rect.width())
            .setHeight(viewport.rect.height())
            .setMinDepth(viewport.min_depth)
            .setMaxDepth(viewport.max_depth);
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
        check_result(_logical_device.waitForFences(fence, VK_TRUE, std::numeric_limits<std::uint64_t>().max()));
        check_result(_logical_device.resetFences(1, &fence));
    }

    void logical_device::create_sync_primitives() noexcept
    {
        const auto semaphore_create_info = vk::SemaphoreCreateInfo();
        const auto fence_create_info     = vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled);

        auto result = _logical_device.createFence(&fence_create_info, nullptr, &_single_time_command_fence);
        check_result(result);

        _fences.resize(_surface_capabilities.minImageCount);
        _image_acquired_semaphores.resize(_surface_capabilities.minImageCount);
        _image_ownership_semaphores.resize(_surface_capabilities.minImageCount);
        _draw_complete_semaphores.resize(_surface_capabilities.minImageCount);

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
        // Command pool for single time commands
        auto st_create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_graphics_queue_family_index)
            .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        auto result = _logical_device.createCommandPool(&st_create_info, nullptr, &_single_time_command_pool);

        check_result(result);

        // Main command pool
        auto create_info = vk::CommandPoolCreateInfo()
            .setQueueFamilyIndex(_present_queue_family_index)
            .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        result = _logical_device.createCommandPool(&create_info, nullptr, &_command_pool);

        check_result(result);
    }

    void logical_device::create_command_buffers() noexcept
    {
        // Command buffers for single time commands
        auto st_allocate_info = vk::CommandBufferAllocateInfo()
            .setCommandPool(_single_time_command_pool)
            .setCommandBufferCount(1)
            .setLevel(vk::CommandBufferLevel::ePrimary);

        auto result = _logical_device.allocateCommandBuffers(&st_allocate_info, &_single_time_command_buffer);

        check_result(result);

        _command_buffers.resize(_swap_chain_images.size());

        // Main command buffers
        auto allocate_info = vk::CommandBufferAllocateInfo()
            .setCommandPool(_command_pool)
            .setCommandBufferCount(static_cast<std::uint32_t>(_swap_chain_images.size()))
            .setLevel(vk::CommandBufferLevel::ePrimary);

        result = _logical_device.allocateCommandBuffers(&allocate_info, _command_buffers.data());

        check_result(result);
    }

    void logical_device::create_image_views() noexcept
    {
        _swap_chain_image_views.resize(_swap_chain_images.size());

        for (std::uint32_t i = 0; i < _swap_chain_images.size(); ++i)
        {
            const auto sub_resource_range = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);

            const auto component_mapping = vk::ComponentMapping()
                .setR(vk::ComponentSwizzle::eIdentity)
                .setG(vk::ComponentSwizzle::eIdentity)
                .setB(vk::ComponentSwizzle::eIdentity)
                .setA(vk::ComponentSwizzle::eIdentity);

            const auto image_view_create_info = vk::ImageViewCreateInfo()
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
            auto result = _logical_device.createImageView(&image_view_create_info, nullptr, &_swap_chain_image_views[i]);

            check_result(result);
        }
    }

    void logical_device::create_render_pass() noexcept
    {
        const vk::AttachmentDescription attachments[2] =
        {
            // For the color attachment, we'll simply be using the swapchain images.
            vk::AttachmentDescription()
                .setFormat(_surface_format.format)
                .setSamples(vk::SampleCountFlagBits::e1)
                .setLoadOp(vk::AttachmentLoadOp::eClear)
                .setStoreOp(vk::AttachmentStoreOp::eStore)
                .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
                .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                .setInitialLayout(vk::ImageLayout::eUndefined)
                .setFinalLayout(vk::ImageLayout::ePresentSrcKHR),

            // For the depth attachment, we'll be using the device depth format.
            vk::AttachmentDescription()
                .setFormat(_depth_format)
                .setSamples(vk::SampleCountFlagBits::e1)
                .setLoadOp(vk::AttachmentLoadOp::eClear)
                .setStoreOp(vk::AttachmentStoreOp::eDontCare)
                .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
                .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
                .setInitialLayout(vk::ImageLayout::eUndefined)
                .setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal)
        };

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
            .setInputAttachmentCount(0)
            .setPInputAttachments(nullptr)
            .setColorAttachmentCount(1)
            .setPColorAttachments(&color_ref)
            .setPreserveAttachmentCount(0)
            .setPResolveAttachments(nullptr)
            .setPDepthStencilAttachment(&depth_ref)
            .setPreserveAttachmentCount(0)
            .setPPreserveAttachments(nullptr);

        auto render_pass_create_info = vk::RenderPassCreateInfo()
            .setAttachmentCount(2)
            .setPAttachments(attachments)
            .setSubpassCount(1)
            .setPSubpasses(&subpass)
            .setDependencyCount(0)
            .setPDependencies(nullptr);

        auto result = _logical_device.createRenderPass(&render_pass_create_info, nullptr, &_render_pass);

        check_result(result);
    }

    void logical_device::create_depth_buffer(vk::Extent2D extent) noexcept
    {
        // Create Image
        auto image_create_info = vk::ImageCreateInfo()
            .setUsage(vk::ImageUsageFlagBits::eDepthStencilAttachment)
            .setImageType(vk::ImageType::e2D)
            .setFormat(_depth_format)
            .setExtent(vk::Extent3D(extent.width, extent.height, 1))
            .setMipLevels(1)
            .setArrayLayers(1)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setTiling(vk::ImageTiling::eOptimal)
            .setSharingMode(vk::SharingMode::eExclusive)
            .setInitialLayout(vk::ImageLayout::eUndefined);

        // Create the image
        VmaAllocationCreateInfo allocation_create_info = { };

        allocation_create_info.usage = VMA_MEMORY_USAGE_CPU_ONLY;

        vk::Image     image;
        VmaAllocation image_allocation;

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

        auto subresource_range = vk::ImageSubresourceRange()
            .setAspectMask(vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil)
            .setBaseMipLevel(0)
            .setLevelCount(1)
            .setBaseArrayLayer(0)
            .setLayerCount(1);

        auto component_mapping = vk::ComponentMapping()
            .setR(vk::ComponentSwizzle::eR)
            .setG(vk::ComponentSwizzle::eG)
            .setB(vk::ComponentSwizzle::eB)
            .setA(vk::ComponentSwizzle::eA);

        auto view_create_info = vk::ImageViewCreateInfo()
            .setImage(image)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(_depth_format)
            .setComponents(component_mapping)
            .setSubresourceRange(subresource_range);

        auto result = _logical_device.createImageView(&view_create_info, nullptr, &image_view);

        check_result(result);

        _depth_buffer = { image, image_view, image_allocation, &_allocator };
    }

    void logical_device::create_frame_buffers(vk::Extent2D extent) noexcept
    {
        destroy_frame_buffers();

        _frame_buffers.resize(_swap_chain_image_views.size());

        vk::ImageView attachments[2];

        attachments[1] = _depth_buffer.view();

        const auto create_info = vk::FramebufferCreateInfo()
            .setRenderPass(_render_pass)
            .setWidth(extent.width)
            .setHeight(extent.height)
            .setAttachmentCount(2)
            .setPAttachments(attachments)
            .setLayers(1);

        for (std::uint32_t i = 0; i < _swap_chain_images.size(); ++i)
        {
            attachments[0] = _swap_chain_image_views[i];

            auto result = _logical_device.createFramebuffer(&create_info, nullptr, &_frame_buffers[i]);

            check_result(result);
        }
    }

    void logical_device::create_pipeline_cache() noexcept
    {
        const auto pipelineCacheInfo = vk::PipelineCacheCreateInfo();
        auto result = _logical_device.createPipelineCache(&pipelineCacheInfo, nullptr, &_pipeline_cache);
        check_result(result);
    }

    vk::DescriptorPool logical_device::create_descriptor_pool(std::uint32_t texture_count) const noexcept
    {
        vk::DescriptorPoolSize const poolSizes[2] =
        {
            vk::DescriptorPoolSize()
                .setType(vk::DescriptorType::eUniformBuffer)
                .setDescriptorCount(static_cast<std::uint32_t>(_swap_chain_images.size())),
            vk::DescriptorPoolSize()
                .setType(vk::DescriptorType::eCombinedImageSampler)
                .setDescriptorCount(static_cast<std::uint32_t>(_swap_chain_images.size() * texture_count))
        };

        const auto descriptor_pool_create_info = vk::DescriptorPoolCreateInfo()
            .setMaxSets(static_cast<std::uint32_t>(_swap_chain_images.size()))
            .setPoolSizeCount(2)
            .setPPoolSizes(poolSizes);

        vk::DescriptorPool descriptor_pool;

        auto result = _logical_device.createDescriptorPool(&descriptor_pool_create_info, nullptr, &descriptor_pool);

        check_result(result);

        return descriptor_pool;
    }

    vk::DescriptorSetLayout logical_device::create_descriptor_layout(std::uint32_t texture_count) const noexcept
    {
        // Pipeline layout
        const vk::DescriptorSetLayoutBinding layout_bindings[2] =
        {
            vk::DescriptorSetLayoutBinding()
                .setBinding(0)
                .setDescriptorType(vk::DescriptorType::eUniformBuffer)
                .setDescriptorCount(1)
                .setStageFlags(vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment)
                .setPImmutableSamplers(nullptr),
            vk::DescriptorSetLayoutBinding()
                .setBinding(1)
                .setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
                .setDescriptorCount(texture_count)
                .setStageFlags(vk::ShaderStageFlagBits::eFragment)
                .setPImmutableSamplers(nullptr)
        };

        const auto descriptor_set_layout_create_info = vk::DescriptorSetLayoutCreateInfo()
            .setBindingCount(2)
            .setPBindings(layout_bindings);

        vk::DescriptorSetLayout descriptor_set_layout;

        auto result = _logical_device.createDescriptorSetLayout(&descriptor_set_layout_create_info, nullptr, &descriptor_set_layout);

        check_result(result);

        return descriptor_set_layout;
    }

    vk::PipelineLayout logical_device::create_pipeline_layout(const vk::DescriptorSetLayout& descriptor_set_layout) const noexcept
    {
        const auto pipeline_layout_create_info = vk::PipelineLayoutCreateInfo()
            .setSetLayoutCount(1)
            .setPSetLayouts(&descriptor_set_layout);

        vk::PipelineLayout pipeline_layout;

        auto result = _logical_device.createPipelineLayout(&pipeline_layout_create_info, nullptr, &pipeline_layout);

        check_result(result);

        return pipeline_layout;
    }

    void logical_device::destroy_sync_primitives() noexcept
    {
        _logical_device.waitIdle();

        _logical_device.waitForFences(1, &_single_time_command_fence, VK_TRUE, std::numeric_limits<std::uint64_t>().max());
        _logical_device.destroyFence(_single_time_command_fence, nullptr);

        for (std::uint32_t i = 0; i < _surface_capabilities.minImageCount; i++)
        {
            _logical_device.waitForFences(1, &_fences[i], VK_TRUE, std::numeric_limits<std::uint64_t>().max());
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
            .setBlendEnable(enabled ? VK_TRUE : VK_FALSE)
            .setColorWriteMask(static_cast<vk::ColorComponentFlagBits>(state.color_write_channels_1))
            .setAlphaBlendOp(static_cast<vk::BlendOp>(state.alpha_blend_function))
            .setSrcAlphaBlendFactor(static_cast<vk::BlendFactor>(state.alpha_source_blend))
            .setDstAlphaBlendFactor(static_cast<vk::BlendFactor>(state.alpha_destination_blend))
            .setColorBlendOp(static_cast<vk::BlendOp>(state.color_blend_function))
            .setSrcColorBlendFactor(static_cast<vk::BlendFactor>(state.color_source_blend))
            .setDstColorBlendFactor(static_cast<vk::BlendFactor>(state.color_destination_blend));

        const auto create_info = vk::PipelineColorBlendStateCreateInfo()
            .setLogicOpEnable(VK_FALSE)
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
