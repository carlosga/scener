// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_INSTANCESKIN_HPP
#define GRAPHICS_INSTANCESKIN_HPP

#include <string>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class ModelMesh;
        class ModelBone;

        class InstanceSkin final
        {
        public:
            InstanceSkin();
            ~InstanceSkin();

        public:
            /**
             * Joint name (jointName property) of skeleton nodes.
             */
            std::vector<std::string> skeletons;

            /**
             * The id (JSON property name) of the skin referenced by this node.
             */
            std::string skin;

            /**
             * The ids (JSON property names) of source meshes.
             */
            std::vector<std::string> meshes;
        };
    }
}

#endif  // GRAPHICS_INSTANCESKIN_HPP
