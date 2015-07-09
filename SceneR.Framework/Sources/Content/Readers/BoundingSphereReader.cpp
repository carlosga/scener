// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BoundingSphereReader.hpp>

#include <Content/ContentReader.hpp>
#include <Framework/BoundingSphere.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Framework::BoundingSphere;

        BoundingSphereReader::BoundingSphereReader()
        {
        }

        BoundingSphereReader::~BoundingSphereReader()
        {
        }

        std::shared_ptr<void> BoundingSphereReader::Read(ContentReader& input)
        {
            return std::make_shared<BoundingSphere>(input.ReadVector3()	    // Center
                                                  , input.ReadSingle());	// Radius
        }
    }
}
