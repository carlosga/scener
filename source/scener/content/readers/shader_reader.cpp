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

    auto content_type_reader<shader>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto type   = value[k_type].get<std::int32_t>();
        auto buffer = input->read_external_reference(value[k_uri].get<std::string>());
        auto stage  = shader_stage::all;

        switch (type)
        {
        case 0x8B30:       // FRAGMENT
            stage = shader_stage::fragment;
            break;

        case 0x8B31:        // VERTEX
            stage = shader_stage::vertex;
            break;

        case 0x8E88:        // TESS CONTROL
            stage = shader_stage::tess_control;
            break;

        case 0x00000004:    // GEOMETRY
            stage = shader_stage::geometry;
            break;

        case 0x00000010:    // TESS EVALUATION
            stage = shader_stage::tess_evaluation;
            break;
        }

        return std::make_shared<shader>(key, stage, buffer);
    }
}

