// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MaterialReader.hpp>

#include <iostream>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/Texture2D.hpp>
#include <System/Text/Encoding.hpp>


namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using SceneR::Graphics::EffectMaterial;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectParameterClass;
        using SceneR::Graphics::EffectTechnique;
        using SceneR::Graphics::Texture2D;
        using System::Text::Encoding;

        ContentTypeReader<EffectMaterial>::ContentTypeReader()
        {
        }

        ContentTypeReader<EffectMaterial>::~ContentTypeReader()
        {
        }

        std::shared_ptr<EffectMaterial> ContentTypeReader<EffectMaterial>::read(ContentReader*                      input
                                                                              , const std::pair<std::string, Json>& source)
        {
            auto effect = std::make_shared<EffectMaterial>();

            const auto& itechnique = source.second["instanceTechnique"];
            const auto& values     = itechnique["values"].object_items();
            const auto  technique  = itechnique["technique"].string_value();

            effect->_name      = Encoding::convert(source.first);
            effect->_technique = input->read_object<EffectTechnique>("techniques", technique);

            for (const auto& value : values)
            {
                auto        parameter  = effect->_technique->_parameters[value.first];
                const auto& paramValue = value.second;

                if (paramValue.is_null())
                {
                }
                else if (parameter->parameter_class() == EffectParameterClass::Scalar)
                {
                    switch (parameter->parameter_type())
                    {
                    case EffectParameterType::Bool:
                        parameter->set_value(paramValue.bool_value());
                        break;
                    case EffectParameterType::Byte:
                        parameter->set_value(static_cast<std::int8_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UByte:
                        parameter->set_value(static_cast<std::uint8_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Int16:
                        parameter->set_value(static_cast<std::int16_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UInt16:
                        parameter->set_value(static_cast<std::uint16_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Int32:
                        parameter->set_value(static_cast<std::int32_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UInt32:
                        parameter->set_value(static_cast<std::uint32_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Single:
                        parameter->set_value(static_cast<float>(paramValue.number_value()));
                        break;
                    case EffectParameterType::String:
                        parameter->set_value<std::u16string>(Encoding::convert(paramValue.string_value()));
                        break;
                    }
                }
                else  if (parameter->parameter_class() == EffectParameterClass::Vector)
                {
                    switch (parameter->column_count())
                    {
                    case 2:
                        parameter->set_value<Vector2>(input->convert<Vector2>(paramValue.array_items()));
                        break;
                    case 3:
                        parameter->set_value<Vector3>(input->convert<Vector3>(paramValue.array_items()));
                        break;
                    case 4:
                        parameter->set_value<Vector4>(input->convert<Vector4>(paramValue.array_items()));
                        break;
                    }
                }
                else if (parameter->parameter_class() == EffectParameterClass::Matrix)
                {
                    parameter->set_value<Matrix>(input->convert<Matrix>(paramValue.array_items()));
                }
                else if (parameter->parameter_class() == EffectParameterClass::Object)
                {
                    effect->_technique->textures().push_back(input->find_object<Texture2D>(paramValue.string_value()));
                }
            }

            return effect;
        }
    }
}
