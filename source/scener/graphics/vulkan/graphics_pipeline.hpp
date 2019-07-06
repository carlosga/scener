// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_GRAPHICS_PIPELINE_HPP
#define SCENER_GRAPHICS_VULKAN_GRAPHICS_PIPELINE_HPP

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

namespace scener::graphics::vulkan
{
    /// Represents a Vulkan graphics pipeline
    class graphics_pipeline final
    {
    public:
        graphics_pipeline() noexcept;
        graphics_pipeline(const vk::DescriptorSetLayout&  descriptor_set_layout
                        , const vk::PipelineLayout&       pipeline_layout
                        , const vk::Pipeline&             pipeline) noexcept;

    public:
        const vk::DescriptorSetLayout& descriptor_set_layout() const noexcept;
        const vk::PipelineLayout& pipeline_layout() const noexcept;
        const vk::Pipeline& pipeline() const noexcept;

    private:
        vk::DescriptorSetLayout  _descriptor_set;
        vk::PipelineLayout _pipeline_layout;
        vk::Pipeline       _pipeline;
    };
}

#endif // SCENER_GRAPHICS_VULKAN_GRAPHICS_PIPELINE_HPP
