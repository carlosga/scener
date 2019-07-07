// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_GRAPHICS_PIPELINE_HPP
#define SCENER_GRAPHICS_VULKAN_GRAPHICS_PIPELINE_HPP

#include <vector>
#include <vulkan/vulkan.hpp>

namespace scener::graphics::vulkan
{
    class logical_device;

    /// Represents a Vulkan graphics pipeline
    class graphics_pipeline final
    {
    public:
        graphics_pipeline() noexcept;
        graphics_pipeline(const vk::Pipeline& pipeline) noexcept;

    public:
        const vk::Pipeline& pipeline() const noexcept;
        const std::vector<vk::DescriptorSet>& descriptors() const noexcept;

    private:        
        vk::Pipeline                   _pipeline;
        std::vector<vk::DescriptorSet> _descriptors;

        friend class scener::graphics::vulkan::logical_device;
    };
}

#endif // SCENER_GRAPHICS_VULKAN_GRAPHICS_PIPELINE_HPP
