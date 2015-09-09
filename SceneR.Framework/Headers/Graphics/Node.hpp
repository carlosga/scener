// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_NODE_HPP
#define GRAPHICS_NODE_HPP

#include <memory>
#include <vector>
#include <string>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class InstanceSkin;
        class ModelMesh;

        class Node
        {
        public:
            Node();
            ~Node();

        public:
            /**
             * The id (JSON property name) of the camera referenced by this node.  A node will have either the camera, light, meshes, or instanceSkin property defined.
             */
            std::string camera;

            /**
             * An instance of a skin.
             */
            std::shared_ptr<InstanceSkin> instanceSkin;

            /**
             * Name used when this node is a joint in a skin.  When this node is a skin, instanceSkin will also be defined.
             */
            std::string jointName;

            /**
             * The id (JSON property name) of the light referenced by this node.  A node will have either the camera, light, meshes, or instanceSkin property defined.
             */
            std::string light;

            /**
             * "A floating-point 4x4 transformation matrix stored in column-major order.  A node will have either a matrix property defined or any combination of rotation, scale, and translation properties defined.  If none are provided, the transform is the identity.  WebGL: see uniformMatrix4fv with the transpose parameter equal to false."
             */
            SceneR::Framework::Matrix matrix;

            /**
             * "The ids (JSON property name) of the meshes in this node.  Multiple meshes are allowed so each can share the same transform matrix.  A node will have either the camera, light, meshes, or instanceSkin property defined."
             */
            std::vector<std::shared_ptr<ModelMesh>> meshes;

            /**
             * The node's quaternion rotation.  A node will have either a matrix property defined or any combination of rotation, scale, and translation properties defined.  If none are provided, the transform is the identity.
             */
            SceneR::Framework::Quaternion rotation;

            /**
             * The node's non-uniform scale.  A node will have either a matrix property defined or any combination of rotation, scale, and translation properties defined.  If none are provided, the transform is the identity.
             */
            SceneR::Framework::Vector3 scale;

            /**
             * The node's translation.  A node will have either a matrix property defined or any combination of rotation, scale, and translation properties defined.  If none are provided, the transform is the identity.
             */
            SceneR::Framework::Vector3 translation;

            /**
             * The ids (JSON property name) of this node's children.
             */
            std::vector<std::string> children;
        };
    }
}

#endif //SCENER_ROOT_NODE_HPP

