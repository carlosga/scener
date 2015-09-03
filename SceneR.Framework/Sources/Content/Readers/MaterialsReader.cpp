// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MaterialsReader.hpp>

#include <iostream>

#include <System/IO/BinaryReader.hpp>
#include <Content/json11.hpp>
#include <GLTF/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::GLTF::Model;
        using SceneR::GLTF::Material;

        MaterialsReader::MaterialsReader()
        {
        }

        MaterialsReader::~MaterialsReader()
        {
        }

        void MaterialsReader::Read(const json11::Json&       value
                                 , System::IO::BinaryReader& reader
                                 , SceneR::GLTF::Model*      root)
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
                        material->ambient = mvalue.second.string_value();
                    }
                    else if (mvalue.first == "bump")
                    {
                        material->bump = mvalue.second.string_value();
                    }
                    else if (mvalue.first == "diffuse")
                    {
                        material->diffuse = mvalue.second.string_value();
                    }
                    else if (mvalue.first == "emission")
                    {
                        const auto& array = mvalue.second.array_items();

                        material->emission = { array[0].number_value()
                                             , array[1].number_value()
                                             , array[2].number_value() };
                    }
                    else if (mvalue.first == "shininess")
                    {
                        material->shininess = mvalue.second.number_value();
                    }
                    else if (mvalue.first == "specular")
                    {
                        const auto& array = mvalue.second.array_items();

                        material->specular = { array[0].number_value()
                                             , array[1].number_value()
                                             , array[2].number_value() };
                    }
                    else
                    {
                        std::cout << "unknown material value [" << mvalue.first << "]" << std::endl;
                    }
                }

                // material->instanceTechnique = root->techniques[item.second["instanceTechnique"].string_value()];

                root->materials[item.first] = material;
            }
        }
    }
}
