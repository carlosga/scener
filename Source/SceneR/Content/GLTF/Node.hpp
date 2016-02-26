// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_NODE_HPP
#define SCENER_CONTENT_GLTF_NODE_HPP

#include <memory>
#include <vector>
#include <string>

#include "scener/math/matrix.hpp"
#include "scener/math/quaternion.hpp"
#include "scener/math/vector.hpp"

namespace scener { namespace graphics {

class Skeleton;
class Bone;
class ModelMesh;

}}

namespace scener { namespace content { namespace gltf {

/// GLTF. A node in the node hierarchy.  Nodes can reference meshes, cameras, lights, or skins.
class Node final
{
public:
    /// Initializes a new instance of the Node class.
    Node() noexcept;

public:
    /// Gets or sets the node name.
    std::string name;

    /// The id (JSON property name) of the camera referenced by this node.
    /// A node will have either the camera, light, meshes, or instanceSkin property defined.
    std::string camera;

    /// An instance of a skin.
    std::shared_ptr<scener::graphics::Skeleton> instance_skin;

    /// A joint in a skin.
    std::shared_ptr<scener::graphics::Bone> joint;

    /// The id (JSON property name) of the light referenced by this node.
    /// A node will have either the camera, light, meshes, or instanceSkin property defined.
    std::string light;

    /// A floating-point 4x4 transformation matrix stored in column-major order.
    /// A node will have either a matrix property defined or any combination of rotation, scale,
    /// and translation properties defined. If none are provided, the transform is the identity.
    scener::math::matrix4 matrix;

    /// The ids (JSON property name) of the meshes in this node.
    /// Multiple meshes are allowed so each can share the same transform matrix.
    /// A node will have either the camera, light, meshes, or instanceSkin property defined.
    std::vector<std::shared_ptr<scener::graphics::ModelMesh>> meshes;

    /// The node's quaternion rotation.
    /// A node will have either a matrix property defined or any combination of rotation, scale,
    /// and translation properties defined. If none are provided, the transform is the identity.
    scener::math::quaternion rotation;

    /// The node's non-uniform scale.
    /// A node will have either a matrix property defined or any combination of rotation, scale,
    /// and translation properties defined. If none are provided, the transform is the identity.
    scener::math::vector3 scale;

    /// The node's translation.
    /// A node will have either a matrix property defined or any combination of rotation, scale,
    /// and translation properties defined.  If none are provided, the transform is the identity.
    scener::math::vector3 translation;

    /// The ids (JSON property name) of this node's children.
    std::vector<std::shared_ptr<Node>> children;
};

}}}

#endif // SCENER_CONTENT_GLTF_NODE_HPP
