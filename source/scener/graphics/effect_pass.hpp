// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECT_PASS_HPP
#define SCENER_GRAPHICS_EFFECT_PASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

namespace scener::content::readers { template <typename T> class content_type_reader; }
namespace scener::graphics::vulkan { class shader; }

namespace scener::graphics
{
    class constant_buffer;
    class effect_parameter;
    class graphics_device;

    /// Contains rendering state for drawing with an effect; an effect can contain one or more passes.
    class effect_pass final
    {
    public:
        /// Gets the name of this pass.
        /// \returns The name of this pass.
        const std::string& name() const noexcept;

        /// Gets the graphics pipeline
        const vk::Pipeline& pipeline() const noexcept;

        /// Gets the effect pass shaders.
        /// \returns the effect pass shaders.
        const std::vector<std::shared_ptr<vulkan::shader>>& shaders() const noexcept;

    private:
        std::vector<std::shared_ptr<effect_parameter>> _parameters      = { };
        std::vector<std::shared_ptr<vulkan::shader>>   _shaders         = { };
        std::string                                    _name            = { };
        std::shared_ptr<constant_buffer>               _constant_buffer = { nullptr };
        vk::UniquePipeline                             _pipeline;

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_EFFECT_PASS_HPP
