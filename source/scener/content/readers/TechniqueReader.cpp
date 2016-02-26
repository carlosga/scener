// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/TechniqueReader.hpp"

#include <json11.hpp>

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/graphics/EffectParameter.hpp"
#include "scener/graphics/EffectPass.hpp"
#include "scener/graphics/EffectTechnique.hpp"
#include "scener/graphics/IGraphicsDeviceService.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/graphics/opengl/Platform.hpp"
#include "scener/graphics/opengl/Program.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::math::matrix4;
using scener::math::vector2;
using scener::math::vector3;
using scener::math::vector4;
using scener::content::gltf::node;
using scener::graphics::EffectTechnique;
using scener::graphics::EffectParameter;
using scener::graphics::EffectParameterClass;
using scener::graphics::EffectParameterType;
using scener::graphics::EffectPass;
using scener::graphics::IGraphicsDeviceService;
using scener::graphics::RendererServiceContainer;
using scener::graphics::opengl::Program;

auto ContentTypeReader<EffectTechnique>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
    auto effect    = std::make_shared<EffectTechnique>(gdService->graphics_device());

    read_parameters(input, source, effect.get());
    add_default_pass(input, source, effect.get());
    cache_parameters(effect.get());
    set_parameter_values(input, source["parameters"], effect.get());

    effect->name = key;

    return effect;
}

void ContentTypeReader<EffectTechnique>::read_parameters(content_reader*   input
                                                       , const Json&      node
                                                       , EffectTechnique* effect) const noexcept
{
    for (const auto& uniform : node["uniforms"].object_items())
    {
        const auto& paramRef  = node["parameters"][uniform.second.string_value()];
        auto        parameter = std::make_shared<EffectParameter>();

        parameter->_name         = uniform.second.string_value();
        parameter->_uniform_name = uniform.first;
        parameter->_count        = static_cast<std::size_t>(paramRef["count"].int_value());

        if (paramRef["node"].is_null() && !paramRef["semantic"].is_null())
        {
            parameter->_semantic = paramRef["semantic"].string_value();
        }

        describe_parameter(parameter.get(), paramRef["type"].int_value());

        effect->_parameters[parameter->_name] = parameter;
    }
}

void ContentTypeReader<EffectTechnique>::set_parameter_values(content_reader*   input
                                                            , const Json&      node
                                                            , EffectTechnique* effect) const noexcept
{
    for (const auto& source : node.object_items())
    {
        const auto  nodeId     = source.second["node"].string_value();
        const auto& paramValue = source.second["value"];
        auto&       parameter  = effect->_parameters[source.first];

        if (parameter == nullptr || paramValue.is_null())
        {
            continue;
        }

        if (!nodeId.empty())
        {
            // TODO: Read node reference
            // auto node = context.find_object<Node>(nodeId);
            // parameter->set_value<matrix4>(node->matrix);
        }
        else if (parameter->parameter_class() == EffectParameterClass::scalar)
        {
            switch (parameter->parameter_type())
            {
            case EffectParameterType::boolean:
                parameter->set_value<bool>(paramValue.bool_value());
                break;
            case EffectParameterType::byte:
                parameter->set_value<std::int8_t>(static_cast<std::int8_t>(paramValue.int_value()));
                break;
            case EffectParameterType::ubyte:
                parameter->set_value<std::uint8_t>(static_cast<std::uint8_t>(paramValue.int_value()));
                break;
            case EffectParameterType::int16:
                parameter->set_value<std::int16_t>(static_cast<std::int16_t>(paramValue.int_value()));
                break;
            case EffectParameterType::uint16:
                parameter->set_value<std::uint16_t>(static_cast<std::uint16_t>(paramValue.int_value()));
                break;
            case EffectParameterType::int32:
                parameter->set_value<std::int32_t>(static_cast<std::int32_t>(paramValue.int_value()));
                break;
            case EffectParameterType::uint32:
                parameter->set_value<std::uint32_t>(static_cast<std::uint32_t>(paramValue.int_value()));
                break;
            case EffectParameterType::single:
                parameter->set_value<float>(static_cast<float>(paramValue.number_value()));
                break;
            case EffectParameterType::string:
            case EffectParameterType::texture:
            case EffectParameterType::texture_1d:
            case EffectParameterType::texture_2d:
            case EffectParameterType::texture_3d:
            case EffectParameterType::texture_cube:
            case EffectParameterType::void_pointer:
                throw std::runtime_error("unknown parameter type");
            }
        }
        else if (parameter->parameter_class() == EffectParameterClass::vector)
        {
            switch (parameter->column_count())
            {
            case 2:
                parameter->set_value(input->convert<vector2>(paramValue.array_items()));
                break;
            case 3:
                parameter->set_value(input->convert<vector3>(paramValue.array_items()));
                break;
            case 4:
                parameter->set_value(input->convert<vector4>(paramValue.array_items()));
                break;
            }
        }
        else if (parameter->parameter_class() == EffectParameterClass::matrix)
        {
            parameter->set_value(input->convert<matrix4>(paramValue.array_items()));
        }
    }
}

void ContentTypeReader<EffectTechnique>::add_default_pass(content_reader*   input
                                                        , const Json&      node
                                                        , EffectTechnique* effect) const noexcept
{
    auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
    auto pass      = std::make_shared<EffectPass>(gdService->graphics_device());

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

void ContentTypeReader<EffectTechnique>::read_pass_program(content_reader*     input
                                                         , const std::string& programName
                                                         , EffectPass*        effectPass) const noexcept
{
    // Pass program
    effectPass->_program = input->read_object_instance<Program>(programName);

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

void ContentTypeReader<EffectTechnique>::cache_parameters(EffectTechnique* technique) const noexcept
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

void ContentTypeReader<EffectTechnique>::describe_parameter(EffectParameter* parameter, std::int32_t type) const noexcept
{
    switch (type)
    {
    case GL_BYTE:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::byte;
        break;

    case GL_UNSIGNED_BYTE:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::byte;
        break;

    case GL_SHORT:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::int16;
        break;

    case GL_UNSIGNED_SHORT:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::uint16;
        break;

    case GL_INT:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::int32;
        break;

    case GL_UNSIGNED_INT:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::uint32;
        break;

    case GL_FLOAT:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::single;
        break;

    case GL_FLOAT_VEC2:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::single;
        parameter->_row_count       = 1;
        parameter->_column_count    = 2;
        break;

    case GL_FLOAT_VEC3:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::single;
        parameter->_row_count       = 1;
        parameter->_column_count    = 3;
        break;

    case GL_FLOAT_VEC4:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::single;
        parameter->_row_count       = 1;
        parameter->_column_count    = 4;
        break;

    case GL_INT_VEC2:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::int32;
        parameter->_row_count       = 1;
        parameter->_column_count    = 2;
        break;

    case GL_INT_VEC3:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::int32;
        parameter->_row_count       = 1;
        parameter->_column_count    = 3;
        break;

    case GL_INT_VEC4:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::int32;
        parameter->_row_count       = 1;
        parameter->_column_count    = 4;
        break;

    case GL_BOOL:
        parameter->_parameter_class = EffectParameterClass::scalar;
        parameter->_parameter_type  = EffectParameterType::boolean;
        break;

    case GL_BOOL_VEC2:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::boolean;
        parameter->_row_count       = 1;
        parameter->_column_count    = 2;
        break;

    case GL_BOOL_VEC3:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::boolean;
        parameter->_row_count       = 1;
        parameter->_column_count    = 3;
        break;

    case GL_BOOL_VEC4:
        parameter->_parameter_class = EffectParameterClass::vector;
        parameter->_parameter_type  = EffectParameterType::boolean;
        parameter->_row_count       = 1;
        parameter->_column_count    = 4;
        break;

    case GL_FLOAT_MAT2	: // mat2
        parameter->_parameter_class = EffectParameterClass::matrix;
        parameter->_parameter_type  = EffectParameterType::single;
        parameter->_row_count       = 2;
        parameter->_column_count    = 2;
        break;

    case GL_FLOAT_MAT3	: // mat3
        parameter->_parameter_class = EffectParameterClass::matrix;
        parameter->_parameter_type  = EffectParameterType::single;
        parameter->_row_count       = 3;
        parameter->_column_count    = 3;
        break;

    case GL_FLOAT_MAT4	: // mat4
        parameter->_parameter_class = EffectParameterClass::matrix;
        parameter->_parameter_type  = EffectParameterType::single;
        parameter->_row_count       = 4;
        parameter->_column_count    = 4;
        break;

    case GL_SAMPLER_2D:
        parameter->_parameter_class = EffectParameterClass::object;
        parameter->_parameter_type  = EffectParameterType::texture_2d;
        break;
    }
}

}}}
