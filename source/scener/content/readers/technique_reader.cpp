// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/technique_reader.hpp"

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/constant_buffer.hpp"
#include "scener/graphics/default_constant_buffer.hpp"
#include "scener/graphics/effect_parameter.hpp"
#include "scener/graphics/effect_pass.hpp"
#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/vulkan/shader.hpp"
#include "scener/graphics/vulkan/shader_module.hpp"

// #define offsetof(st, m) __builtin_offsetof(st, m)

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::math::matrix4;
    using scener::math::vector2;
    using scener::math::vector3;
    using scener::math::vector4;
    using scener::content::gltf::node;
    using scener::graphics::constant_buffer;
    using scener::graphics::effect_technique;
    using scener::graphics::effect_parameter;
    using scener::graphics::effect_parameter_class;
    using scener::graphics::effect_parameter_type;
    using scener::graphics::effect_pass;
    using scener::graphics::igraphics_device_service;
    using scener::graphics::service_container;
    using scener::graphics::vulkan::shader;
    using scener::graphics::vulkan::shader_module;
    using namespace scener::content::gltf;

    auto content_type_reader<effect_technique>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto instance  = std::make_shared<effect_technique>(gdservice->device());

        read_parameters(input, value, instance.get());
        add_default_pass(input, value, instance.get());
        cache_parameters(instance.get());
        set_parameter_values(input, value[k_parameters], instance.get());

        instance->name = key;

        return instance;
    }

    void content_type_reader<effect_technique>::read_parameters([[maybe_unused]]  content_reader* input
                                                              , const json&       value
                                                              , effect_technique* effect) const noexcept
    {
        std::uint32_t offset = 0;

        for (auto it = value[k_uniforms].begin(); it != value[k_uniforms].end(); ++it)
        {
            const auto    uniform_name = it.value().get<std::string>();
            const auto&   paramref     = value[k_parameters][uniform_name];
            auto          parameter    = std::make_shared<effect_parameter>();

            parameter->_name         = uniform_name;
            parameter->_uniform_name = it.key();            

            if (paramref.count(k_count) != 0)
            {
                parameter->_count = paramref[k_count].get<std::uint32_t>();
            }
            else
            {
                parameter->_count = 1;
            }
            if (paramref.count(k_semantic) != 0)
            {
                parameter->_semantic = paramref[k_semantic].get<std::string>();
            }

            describe_parameter(parameter.get(), paramref[k_type].get<std::int32_t>());

            if (parameter->_uniform_name == "u_jointMat")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_jointMat);
            }
            else if (parameter->_uniform_name == "u_normalMatrix")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_normalMatrix);
            }
            else if (parameter->_uniform_name == "u_modelViewMatrix")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_modelViewMatrix);
            }
            else if (parameter->_uniform_name == "u_projectionMatrix")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_projectionMatrix);
            }
            else if (parameter->_uniform_name == "u_light0Transform")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_light0Transform);
            }
            else if (parameter->_uniform_name == "u_ambient")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_ambient);
            }
            else if (parameter->_uniform_name == "u_emission")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_emission);
            }
            else if (parameter->_uniform_name == "u_specular")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_specular);
            }
            else if (parameter->_uniform_name == "u_shininess")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_shininess);
            }
            else if (parameter->_uniform_name == "u_light0ConstantAttenuation")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_light0ConstantAttenuation);
            }
            else if (parameter->_uniform_name == "u_light0LinearAttenuation")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_light0LinearAttenuation);
            }
            else if (parameter->_uniform_name == "u_light0QuadraticAttenuation")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_light0QuadraticAttenuation);
            }
            else if (parameter->_uniform_name == "u_light0Color")
            {
                offset = offsetof(scener::graphics::default_constant_buffer, u_light0Color);
            }

            parameter->_offset = offset;

            effect->_parameters[parameter->_name] = parameter;
        }
    }

    void content_type_reader<effect_technique>::set_parameter_values(content_reader*       input
                                                                   , const nlohmann::json& value
                                                                   , effect_technique*     effect) const noexcept
    {
        for (auto it = value.begin(); it != value.end(); ++it)
        {
            const auto& key     = it.key();
            const auto& current = it.value();

            if (current.count(k_value) == 0)
            {
                continue;
            }

            const auto& parameter = effect->_parameters[key];

            if (parameter == nullptr)
            {
                continue;
            }

            const auto& pvalue = current[k_value];

            if (current.count(k_node) != 0)
            {
                // const auto nodeId = it.value()["node"].get<std::string>();

                // TODO: Read node reference
                // auto node = context.find_object<Node>(nodeId);
                // parameter->set_value<matrix4>(node->matrix);
            }
            else if (parameter->parameter_class() == effect_parameter_class::scalar)
            {
                switch (parameter->parameter_type())
                {
                case effect_parameter_type::boolean:
                    parameter->set_value<bool>(pvalue.get<bool>());
                    break;
                case effect_parameter_type::byte:
                    parameter->set_value<std::int8_t>(pvalue.get<std::int8_t>());
                    break;
                case effect_parameter_type::ubyte:
                    parameter->set_value<std::uint8_t>(pvalue.get<std::uint8_t>());
                    break;
                case effect_parameter_type::int16:
                    parameter->set_value<std::int16_t>(pvalue.get<std::int16_t>());
                    break;
                case effect_parameter_type::uint16:
                    parameter->set_value<std::uint16_t>(pvalue.get<std::uint16_t>());
                    break;
                case effect_parameter_type::int32:
                    parameter->set_value<std::int32_t>(pvalue.get<std::int32_t>());
                    break;
                case effect_parameter_type::uint32:
                    parameter->set_value<std::uint32_t>(pvalue.get<std::uint32_t>());
                    break;
                case effect_parameter_type::single:
                    parameter->set_value<float>(pvalue.get<float>());
                    break;
                default:
                    throw std::runtime_error("unknown parameter type");
                }
            }
            else if (parameter->parameter_class() == effect_parameter_class::vector)
            {
                switch (parameter->column_count())
                {
                case 2:
                    parameter->set_value<vector2>(input->convert<vector2>(pvalue.get<json::array_t>()));
                    break;
                case 3:
                    parameter->set_value<vector3>(input->convert<vector3>(pvalue.get<json::array_t>()));
                    break;
                case 4:
                    parameter->set_value<vector4>(input->convert<vector4>(pvalue.get<json::array_t>()));
                    break;
                }
            }
            else if (parameter->parameter_class() == effect_parameter_class::matrix)
            {
                parameter->set_value(input->convert<matrix4>(pvalue.get<json::array_t>()));
            }
        }
    }

    void content_type_reader<effect_technique>::add_default_pass(content_reader*       input
                                                               , const nlohmann::json& value
                                                               , effect_technique*     effect) const noexcept
    {
        auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto device    = gdservice->device();
        auto pass      = std::make_shared<effect_pass>();

        pass->_name            = "default_pass";
        pass->_constant_buffer = std::make_shared<constant_buffer>(device, "constant_buffer", sizeof(graphics::default_constant_buffer));
        pass->_parameters.reserve(effect->_parameters.size());

        for (const auto& param : effect->_parameters)
        {
            param.second->_constant_buffer = pass->_constant_buffer;
            pass->_parameters.push_back(param.second);
        }

        // Shader module
        pass->_shader_module = input->read_object_instance<shader_module>(value[k_program].get<std::string>());

        effect->_passes.push_back(pass);
    }

    void content_type_reader<effect_technique>::cache_parameters(effect_technique* technique) const noexcept
    {
        for (const auto& parameter : technique->_parameters)
        {
            if (parameter.second->_semantic.empty())
            {
                continue;
            }

            if (parameter.second->_semantic == k_model)
            {
                technique->_world_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_view)
            {
                technique->_view_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_projection)
            {
                technique->_projection_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_view)
            {
                technique->_world_view_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_view_projection)
            {
                technique->_world_view_projection_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_inverse)
            {
                technique->_world_inverse_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_view_inverse)
            {
                technique->_view_inverse_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_projection_inverse)
            {
                technique->_projection_inverse_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_view_inverse)
            {
                technique->_world_view_inverse_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_view_projection_inverse)
            {
                technique->_world_view_projection_inverse_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_inverse_transpose)
            {
                technique->_world_inverse_transpose_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_model_view_inverse_transpose)
            {
                technique->_world_view_inverse_transpose_param = parameter.second;
            }
            else if (parameter.second->_semantic == k_joint_matrix)
            {
                technique->_bones_param = parameter.second;
            }
            else
            {
                throw std::runtime_error("Unknown semantic.");
            }
        }
    }

    void content_type_reader<effect_technique>::describe_parameter(effect_parameter* parameter, std::int32_t type) const noexcept
    {        
        switch (type)
        {
        case 0x1400:    // byte
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::byte;
            parameter->_size            = sizeof (std::int8_t) * parameter->_count;
            break;

        case 0x1401:    // unsigned byte
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::byte;
            parameter->_size            = sizeof (std::uint8_t) * parameter->_count;
            break;

        case 0x1402:    // short
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::int16;
            parameter->_size            = sizeof (std::int16_t) * parameter->_count;
            break;

        case 0x1403:    // unsigned short
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::uint16;
            parameter->_size            = sizeof (std::uint16_t) * parameter->_count;
            break;

        case 0x1404:    // int
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::int32;
            parameter->_size            = sizeof (std::int32_t) * parameter->_count;
            break;

        case 0x1405:    // unsigned int
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::uint32;
            parameter->_size            = sizeof (std::uint32_t) * parameter->_count;
            break;

        case 0x1406:    // float
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_size            = sizeof (float) * parameter->_count;
            break;

        case 0x8B50:    // vec2f
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_row_count       = 1;
            parameter->_column_count    = 2;
            parameter->_size            = sizeof (math::vector2) * parameter->_count;
            break;

        case 0x8B51:    // vec3f
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_row_count       = 1;
            parameter->_column_count    = 3;
            parameter->_size            = sizeof (math::vector3) * parameter->_count;
            break;

        case 0x8B52:    // vec4f
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_row_count       = 1;
            parameter->_column_count    = 4;
            parameter->_size            = sizeof (math::vector4) * parameter->_count;
            break;

        case 0x8B53:    // vec2i
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::int32;
            parameter->_row_count       = 1;
            parameter->_column_count    = 2;
            parameter->_size            = sizeof (math::vector2i) * parameter->_count;
            break;

        case 0x8B54:    // vec3i
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::int32;
            parameter->_row_count       = 1;
            parameter->_column_count    = 3;
            parameter->_size            = sizeof (math::vector3i) * parameter->_count;
            break;

        case 0x8B55:    // vec4i
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::int32;
            parameter->_row_count       = 1;
            parameter->_column_count    = 4;
            parameter->_size            = sizeof (math::vector4i) * parameter->_count;
            break;

        case 0x8B56:    // bool
            parameter->_parameter_class = effect_parameter_class::scalar;
            parameter->_parameter_type  = effect_parameter_type::boolean;
            parameter->_size            = sizeof (bool) * parameter->_count;
            break;

        case 0x8B57:    // vec2b
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::boolean;
            parameter->_row_count       = 1;
            parameter->_column_count    = 2;
            parameter->_size            = sizeof (bool) * 2 * parameter->_count;
            break;

        case 0x8B58:    // vec3b
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::boolean;
            parameter->_row_count       = 1;
            parameter->_column_count    = 3;
            parameter->_size            = sizeof (bool) * 3 * parameter->_count;
            break;

        case 0x8B59:    // vec4b
            parameter->_parameter_class = effect_parameter_class::vector;
            parameter->_parameter_type  = effect_parameter_type::boolean;
            parameter->_row_count       = 1;
            parameter->_column_count    = 4;
            parameter->_size            = sizeof (bool) * 4 * parameter->_count;
            break;

        case 0x8B5A	:   // mat2f
            parameter->_parameter_class = effect_parameter_class::matrix;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_row_count       = 2;
            parameter->_column_count    = 2;
            parameter->_size            = sizeof (math::matrix2) * parameter->_count;
            break;

        case 0x8B5B	:   // mat3f
            parameter->_parameter_class = effect_parameter_class::matrix;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_row_count       = 3;
            parameter->_column_count    = 3;
            parameter->_size            = sizeof (math::matrix3) * parameter->_count;
            break;

        case 0x8B5C	:   // mat4f
            parameter->_parameter_class = effect_parameter_class::matrix;
            parameter->_parameter_type  = effect_parameter_type::single;
            parameter->_row_count       = 4;
            parameter->_column_count    = 4;
            parameter->_size            = sizeof (math::matrix4) * parameter->_count;
            break;

        case 0x8B5E:    // sampler 2d
            parameter->_parameter_class = effect_parameter_class::object;
            parameter->_parameter_type  = effect_parameter_type::texture_2d;
            break;
        }
    }
}
