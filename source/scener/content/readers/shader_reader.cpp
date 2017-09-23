// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/shader_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/vulkan/shader.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::vulkan::shader;
    using scener::graphics::vulkan::shader_stage;
    using namespace scener::content::gltf;

    auto content_type_reader<shader>::read(content_reader* input, const std::string& key, const json& value) const noexcept
    {
        auto stage  = static_cast<shader_stage>(value[k_type].get<std::int32_t>());
        auto buffer = input->read_external_reference(value[k_uri].get<std::string>());

        return std::make_shared<shader>(key, stage, buffer);
    }
}

