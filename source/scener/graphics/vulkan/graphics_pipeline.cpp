#include "scener/graphics/vulkan/graphics_pipeline.hpp"

namespace scener::graphics::vulkan
{
    graphics_pipeline::graphics_pipeline() noexcept
        : _pipeline { }
        , _descriptors { }
    {
    }

    graphics_pipeline::graphics_pipeline(const vk::Pipeline& pipeline) noexcept
        : _pipeline    { pipeline }
        , _descriptors { }
    {
    }

    const vk::Pipeline& graphics_pipeline::pipeline() const noexcept
    {
        return _pipeline;
    }

    const std::vector<vk::DescriptorSet>& graphics_pipeline::descriptors() const noexcept
    {
        return _descriptors;
    }
}
