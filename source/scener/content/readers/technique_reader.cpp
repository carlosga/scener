// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/technique_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/graphics/EffectParameter.hpp"
#include "scener/graphics/EffectPass.hpp"
#include "scener/graphics/EffectTechnique.hpp"
#include "scener/graphics/IGraphicsDeviceService.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/graphics/opengl/platform.hpp"
#include "scener/graphics/opengl/program.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::math::matrix4;
using scener::math::vector2;
using scener::math::vector3;
using scener::math::vector4;
using scener::content::gltf::node;
using scener::graphics::effect_technique;
using scener::graphics::effect_parameter;
using scener::graphics::effect_parameter_class;
using scener::graphics::effect_parameter_type;
using scener::graphics::effect_pass;
using scener::graphics::igraphics_device_service;
using scener::graphics::service_container;
using scener::graphics::opengl::program;

auto content_type_reader<effect_technique>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
    auto effect    = std::make_shared<effect_technique>(gdservice->device());

    read_parameters(input, source, effect.get());
    add_default_pass(input, source, effect.get());
    cache_parameters(effect.get());
    set_parameter_values(input, source["parameters"], effect.get());

    effect->name = key;

    return effect;
}

void content_type_reader<effect_technique>::read_parameters(content_reader*   input
                                                        , const Json&       node
                                                        , effect_technique* effect) const noexcept
{
    for (const auto& uniform : node["uniforms"].object_items())
    {
        const auto& paramref  = node["parameters"][uniform.second.string_value()];
        auto        parameter = std::make_shared<effect_parameter>();

        parameter->_name         = uniform.second.string_value();
        parameter->_uniform_name = uniform.first;
        parameter->_count        = static_cast<std::size_t>(paramref["count"].int_value());

        if (paramref["node"].is_null() && !paramref["semantic"].is_null())
        {
            parameter->_semantic = paramref["semantic"].string_value();
        }

        describe_parameter(parameter.get(), paramref["type"].int_value());

        effect->_parameters[parameter->_name] = parameter;
    }
}

void content_type_reader<effect_technique>::set_parameter_values(content_reader*   input
                                                            , const Json&      node
                                                            , effect_technique* effect) const noexcept
{
    for (const auto& source : node.object_items())
    {
        const auto  nodeId    = source.second["node"].string_value();
        const auto& pvalue    = source.second["value"];
        auto&       parameter = effect->_parameters[source.first];

        if (parameter == nullptr || pvalue.is_null())
        {
            continue;
        }

        if (!nodeId.empty())
        {
            // TODO: Read node reference
            // auto node = context.find_object<Node>(nodeId);
            // parameter->set_value<matrix4>(node->matrix);
        }
        else if (parameter->parameter_class() == effect_parameter_class::scalar)
        {
            switch (parameter->parameter_type())
            {
            case effect_parameter_type::boolean:
                parameter->set_value<bool>(pvalue.bool_value());
                break;
            case effect_parameter_type::byte:
                parameter->set_value<std::int8_t>(static_cast<std::int8_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::ubyte:
                parameter->set_value<std::uint8_t>(static_cast<std::uint8_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::int16:
                parameter->set_value<std::int16_t>(static_cast<std::int16_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::uint16:
                parameter->set_value<std::uint16_t>(static_cast<std::uint16_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::int32:
                parameter->set_value<std::int32_t>(static_cast<std::int32_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::uint32:
                parameter->set_value<std::uint32_t>(static_cast<std::uint32_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::single:
                parameter->set_value<float>(static_cast<float>(pvalue.number_value()));
                break;
            case effect_parameter_type::string:
            case effect_parameter_type::texture:
            case effect_parameter_type::texture_1d:
            case effect_parameter_type::texture_2d:
            case effect_parameter_type::texture_3d:
            case effect_parameter_type::texture_cube:
            case effect_parameter_type::void_pointer:
                throw std::runtime_error("unknown parameter type");
            }
        }
        else if (parameter->parameter_class() == effect_parameter_class::vector)
        {
            switch (parameter->column_count())
            {
            case 2:
                parameter->set_value(input->convert<vector2>(pvalue.array_items()));
                break;
            case 3:
                parameter->set_value(input->convert<vector3>(pvalue.array_items()));
                break;
            case 4:
                parameter->set_value(input->convert<vector4>(pvalue.array_items()));
                break;
            }
        }
        else if (parameter->parameter_class() == effect_parameter_class::matrix)
        {
            parameter->set_value(input->convert<matrix4>(pvalue.array_items()));
        }
    }
}

void content_type_reader<effect_technique>::add_default_pass(content_reader*   input
                                                        , const Json&      node
                                                        , effect_technique* effect) const noexcept
{
    auto gdservice = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
    auto pass      = std::make_shared<effect_pass>(gdservice->device());

    pass->_name = "default_pass";
    pass->_parameters.reserve(effect->_parameters.size());

    for (const auto& param : effect->_parameters)
    {
        pass->_parameters.push_back(param.second);
    }

    read_pass_program(input, node["program"].string_value(), pass.get());

    effect->_passes.push_back(pass);
    effect->_pass = pass;
}

void content_type_reader<effect_technique>::read_pass_program(content_reader*     input
                                                         , const std::string& programName
                                                         , effect_pass*        effectPass) const noexcept
{
    // Pass program
    effectPass->_program = input->read_object_instance<program>(programName);

    // Uniforms
    auto offsets = effectPass->_program->get_uniform_offsets();

    for (const auto& parameter : effectPass->_parameters)
    {
        if (offsets.find(parameter->_uniform_name) != offsets.end())
        {
            parameter->_offset          = offsets[parameter->_uniform_name];
            parameter->_constant_buffer = effectPass->_program->constant_buffer();
        }
    }
}

void content_type_reader<effect_technique>::cache_parameters(effect_technique* technique) const noexcept
{
    for (const auto& parameter : technique->_parameters)
    {
        if (parameter.second->_semantic.empty())
        {
            continue;
        }

        if (parameter.second->_semantic == "MODEL")
        {
            technique->_world_param = parameter.second;
        }
        else if (parameter.second->_semantic == "VIEW")
        {
            technique->_view_param = parameter.second;
        }
        else if (parameter.second->_semantic == "PROJECTION")
        {
            technique->_projection_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELVIEW")
        {
            technique->_world_view_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELVIEWPROJECTION")
        {
            technique->_world_view_projection_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELINVERSE")
        {
            technique->_world_inverse_param = parameter.second;
        }
        else if (parameter.second->_semantic == "VIEWINVERSE")
        {
            technique->_view_inverse_param = parameter.second;
        }
        else if (parameter.second->_semantic == "PROJECTIONINVERSE")
        {
            technique->_projection_inverse_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELVIEWINVERSE")
        {
            technique->_world_view_inverse_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELVIEWPROJECTIONINVERSE")
        {
            technique->_world_view_projection_inverse_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELINVERSETRANSPOSE")
        {
            technique->_world_inverse_transpose_param = parameter.second;
        }
        else if (parameter.second->_semantic == "MODELVIEWINVERSETRANSPOSE")
        {
            technique->_world_view_inverse_transpose_param = parameter.second;
        }
        else if (parameter.second->_semantic == "JOINTMATRIX")
        {
            technique->_bones_param = parameter.second;
        }
    }
}

void content_type_reader<effect_technique>::describe_parameter(effect_parameter* parameter, std::int32_t type) const noexcept
{
    switch (type)
    {
    case GL_BYTE:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::byte;
        break;

    case GL_UNSIGNED_BYTE:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::byte;
        break;

    case GL_SHORT:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::int16;
        break;

    case GL_UNSIGNED_SHORT:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::uint16;
        break;

    case GL_INT:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::int32;
        break;

    case GL_UNSIGNED_INT:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::uint32;
        break;

    case GL_FLOAT:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::single;
        break;

    case GL_FLOAT_VEC2:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::single;
        parameter->_row_count       = 1;
        parameter->_column_count    = 2;
        break;

    case GL_FLOAT_VEC3:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::single;
        parameter->_row_count       = 1;
        parameter->_column_count    = 3;
        break;

    case GL_FLOAT_VEC4:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::single;
        parameter->_row_count       = 1;
        parameter->_column_count    = 4;
        break;

    case GL_INT_VEC2:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::int32;
        parameter->_row_count       = 1;
        parameter->_column_count    = 2;
        break;

    case GL_INT_VEC3:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::int32;
        parameter->_row_count       = 1;
        parameter->_column_count    = 3;
        break;

    case GL_INT_VEC4:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::int32;
        parameter->_row_count       = 1;
        parameter->_column_count    = 4;
        break;

    case GL_BOOL:
        parameter->_parameter_class = effect_parameter_class::scalar;
        parameter->_parameter_type  = effect_parameter_type::boolean;
        break;

    case GL_BOOL_VEC2:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::boolean;
        parameter->_row_count       = 1;
        parameter->_column_count    = 2;
        break;

    case GL_BOOL_VEC3:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::boolean;
        parameter->_row_count       = 1;
        parameter->_column_count    = 3;
        break;

    case GL_BOOL_VEC4:
        parameter->_parameter_class = effect_parameter_class::vector;
        parameter->_parameter_type  = effect_parameter_type::boolean;
        parameter->_row_count       = 1;
        parameter->_column_count    = 4;
        break;

    case GL_FLOAT_MAT2	: // mat2
        parameter->_parameter_class = effect_parameter_class::matrix;
        parameter->_parameter_type  = effect_parameter_type::single;
        parameter->_row_count       = 2;
        parameter->_column_count    = 2;
        break;

    case GL_FLOAT_MAT3	: // mat3
        parameter->_parameter_class = effect_parameter_class::matrix;
        parameter->_parameter_type  = effect_parameter_type::single;
        parameter->_row_count       = 3;
        parameter->_column_count    = 3;
        break;

    case GL_FLOAT_MAT4	: // mat4
        parameter->_parameter_class = effect_parameter_class::matrix;
        parameter->_parameter_type  = effect_parameter_type::single;
        parameter->_row_count       = 4;
        parameter->_column_count    = 4;
        break;

    case GL_SAMPLER_2D:
        parameter->_parameter_class = effect_parameter_class::object;
        parameter->_parameter_type  = effect_parameter_type::texture_2d;
        break;
    }
}

}}}
