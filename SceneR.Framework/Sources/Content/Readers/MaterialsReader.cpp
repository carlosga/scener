// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MaterialsReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Material.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::Material;
        using System::Text::Encoding;

        MaterialsReader::MaterialsReader()
        {
        }

        MaterialsReader::~MaterialsReader()
        {
        }

        void MaterialsReader::read(const json11::Json&               value
                                 , SceneR::Graphics::GraphicsDevice& graphicsDevice
                                 , SceneR::Graphics::Model*          root)
        {
            for (const auto& item : value["materials"].object_items())
            {
                auto material = std::make_shared<Material>();

                const auto& instanceTechnique = item.second["instanceTechnique"];
                const auto& values            = instanceTechnique["values"].object_items();

                for (const auto& mvalue : values)
                {
                    if (mvalue.first == "ambient")
                    {
                        material->_ambient = mvalue.second.string_value();
                    }
                    else if (mvalue.first == "bump")
                    {
                        material->_bump = mvalue.second.string_value();
                    }
                    else if (mvalue.first == "diffuse")
                    {
                        material->_diffuse = mvalue.second.string_value();
                    }
                    else if (mvalue.first == "emission")
                    {
                        const auto& array = mvalue.second.array_items();

                        material->_emission = { array[0].number_value()
                                              , array[1].number_value()
                                              , array[2].number_value() };
                    }
                    else if (mvalue.first == "shininess")
                    {
                        material->_shininess = mvalue.second.number_value();
                    }
                    else if (mvalue.first == "specular")
                    {
                        const auto& array = mvalue.second.array_items();

                        material->_specular = { array[0].number_value()
                                              , array[1].number_value()
                                              , array[2].number_value() };
                    }
                    else
                    {
                        std::cout << "unknown material value [" << mvalue.first << "]" << std::endl;
                    }
                }

                material->_name = Encoding::convert(item.first);

                // TODO: Decode material instance technique
                // material->instanceTechnique = root->techniques[item.second["instanceTechnique"].string_value()];

                root->_materials.push_back(material);
            }
        }
    }
}
