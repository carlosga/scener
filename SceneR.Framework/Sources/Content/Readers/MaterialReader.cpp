// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MaterialReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::EffectMaterial;
        using SceneR::Graphics::EffectTechnique;
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

            effect->_technique = input->read_object<EffectTechnique>("techniques", technique);

            for (const auto& value : values)
            {
                if (value.first == "ambient")
                {
                    effect->_ambient = value.second.string_value();
                }
                else if (value.first == "bump")
                {
                    effect->_bump = value.second.string_value();
                }
                else if (value.first == "diffuse")
                {
                    effect->_diffuse = value.second.string_value();
                }
                else if (value.first == "emission")
                {
                    const auto& array = value.second.array_items();

                    effect->_emission = { array[0].number_value()
                                          , array[1].number_value()
                                          , array[2].number_value() };
                }
                else if (value.first == "shininess")
                {
                    effect->_shininess = value.second.number_value();
                }
                else if (value.first == "specular")
                {
                    const auto& array = value.second.array_items();

                    effect->_specular = { array[0].number_value()
                                        , array[1].number_value()
                                        , array[2].number_value() };
                }
                else
                {
                    std::cout << "unknown material value [" << value.first << "]" << std::endl;
                }
            }

            effect->_name = Encoding::convert(source.first);

            // TODO: Decode material instance technique
            // material->instanceTechnique = root->techniques[item.second["instanceTechnique"].string_value()];

            return effect;
        }
    }
}
