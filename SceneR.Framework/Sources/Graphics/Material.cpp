// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Material.hpp>

namespace SceneR
{
    namespace Graphics
    {

        Material::Material()
        {

        }

        Material::~Material()
        {

        }

        const std::u16string& Material::name() const
        {
            return _name;
        }
    }
}

