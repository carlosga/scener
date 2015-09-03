// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <System/IO/BinaryReader.hpp>
#include <GLTF/Model.hpp>
#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::BinaryReader;
        using SceneR::GLTF::Technique;
        using json11::Json;

        TechniquesReader::TechniquesReader()
        {
        }

        TechniquesReader::~TechniquesReader()
        {
        }

        void TechniquesReader::Read(const json11::Json&       value
                                  , System::IO::BinaryReader& reader
                                  , SceneR::GLTF::Model*      root)
        {
            for (const auto& item : value["techniques"].object_items())
            {
                std::cout << item.second.dump() << std::endl;
            }
        }
    }
}
