// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/EffectMaterialReader.hpp>

#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        EffectMaterialReader::EffectMaterialReader()
        {
        }

        EffectMaterialReader::~EffectMaterialReader()
        {
        }

        std::shared_ptr<void> EffectMaterialReader::Read(ContentReader& input)
        {
            // ExternalReference                  Effect       Pointer to a separate .xnb file which contains an object of type Effect
            // Object: Dictionary<String, Object> Parameters   Named parameter values. Supported types:
            //                                                     Int32
            //                                                     Boolean
            //                                                     Single
            //                                                     Vector2
            //                                                     Vector3
            //                                                     Vector4
            //                                                     Matrix
            //                                                     Arrays of any of the above
            //                                                     Texture (commonly stored as an ExternalReference which points to a separate .xnb file)
            //                                                     String

            return nullptr;
        }
    }
}
