// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/program_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/vulkan/shader.hpp"
#include "scener/graphics/vulkan/shader_module.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::vulkan::shader_module;
    using scener::graphics::vulkan::shader;
    using namespace scener::content::gltf;

    auto content_type_reader<shader_module>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<shader_module>();
        auto vshader  = value[k_vertex_shader].get<std::string>();
        auto fshader  = value[k_fragment_shader].get<std::string>();

        instance->name = key;

        instance->_shaders.push_back(input->read_object<shader>(vshader));
        instance->_shaders.push_back(input->read_object<shader>(fshader));

        return instance;
    }
}

