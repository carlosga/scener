#include "scener/graphics/vulkan/graphics_pipeline.hpp"

namespace scener::graphics::vulkan
{
    graphics_pipeline::graphics_pipeline() noexcept
        : _pipeline              { }
        , _pipeline_layout       { }
        , _descriptor_pool       { }
        , _descriptor_set_layout { }
        , _descriptors           { }
    {
    }

    graphics_pipeline::graphics_pipeline(const vk::Pipeline&                   pipeline
                                       , const vk::PipelineLayout&             pipeline_layout
                                       , const vk::DescriptorPool&             descriptor_pool
                                       , const vk::DescriptorSetLayout&        descriptor_set_layout
                                       , const std::vector<vk::DescriptorSet>& descriptors) noexcept
        : _pipeline              { pipeline }
        , _pipeline_layout       { pipeline_layout }
        , _descriptor_pool       { descriptor_pool }
        , _descriptor_set_layout { descriptor_set_layout }
        , _descriptors           { descriptors }
    {
    }

    const vk::Pipeline& graphics_pipeline::pipeline() const noexcept
    {
        return _pipeline;
    }

    const vk::PipelineLayout& graphics_pipeline::pipeline_layout() const noexcept
    {
        return _pipeline_layout;
    }

    const std::vector<vk::DescriptorSet>& graphics_pipeline::descriptors() const noexcept
    {
        return _descriptors;
    }
}
