#include "scener/graphics/vulkan/graphics_pipeline.hpp"

namespace scener::graphics::vulkan
{
    graphics_pipeline::graphics_pipeline() noexcept
        : _descriptor_set  { }
        , _pipeline_layout { }
        , _pipeline        { }
    {
    }

    graphics_pipeline::graphics_pipeline(const vk::DescriptorSetLayout&  descriptor_set
                                       , const vk::PipelineLayout&       pipeline_layout
                                       , const vk::Pipeline&             pipeline) noexcept
        : _descriptor_set  { descriptor_set }
        , _pipeline_layout { pipeline_layout }
        , _pipeline        { pipeline }
    {
    }

    const vk::DescriptorSetLayout& graphics_pipeline::descriptor_set_layout() const noexcept
    {
        return _descriptor_set;
    }

    const vk::PipelineLayout& graphics_pipeline::pipeline_layout() const noexcept
    {
        return _pipeline_layout;
    }

    const vk::Pipeline& graphics_pipeline::pipeline() const noexcept
    {
        return _pipeline;
    }
}
