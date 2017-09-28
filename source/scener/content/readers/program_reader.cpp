// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/program_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/vulkan/program.hpp"
#include "scener/graphics/vulkan/shader.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::vulkan::program;
    using scener::graphics::vulkan::shader;
    using namespace scener::content::gltf;

    auto content_type_reader<program>::read(content_reader* input, const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<program>();
        auto vshader  = value[k_vertex_shader].get<std::string>();
        auto fshader  = value[k_fragment_shader].get<std::string>();

        instance->name = key;
        instance->add_shader(input->read_object<shader>(vshader));
        instance->add_shader(input->read_object<shader>(fshader));

        return instance;
    }
}
