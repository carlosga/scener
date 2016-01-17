// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/SkeletonReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/GLTF/Accessor.hpp"
#include "SceneR/Graphics/Skeleton.hpp"
#include "SceneR/Math/Matrix.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Content::GLTF::Accessor;
using SceneR::Graphics::Skeleton;
using SceneR::Math::Matrix;

auto ContentTypeReader<Skeleton>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto skeleton = std::make_shared<Skeleton>();
    auto accessor = input->read_object<Accessor>(source["inverseBindMatrices"].string_value());

    // Name
    skeleton->_name = key;

    // Bind shape matrix
    skeleton->_bind_shape_matrix = input->convert<Matrix>(source["bindShapeMatrix"].array_items());

    // Inverse bind matrices
    skeleton->_inverse_bind_matrices.reserve(accessor->attribute_count());

    for (std::size_t i = 0; i < accessor->attribute_count(); i++)
    {
        skeleton->_inverse_bind_matrices.push_back(accessor->get_element<Matrix>(i));
    }

    // Joints
    auto jointNames = source["jointNames"].array_items();
    auto boneIndex  = std::size_t { 0 };
    auto jointCount = jointNames.size();

    skeleton->_joints.reserve(jointCount);
    skeleton->_bone_transforms.reserve(jointCount);

    for (const auto& jointName : jointNames)
    {
        auto node = input->find_joint_node(jointName.string_value());

        Ensures(node.get() != nullptr && node->joint.get() != nullptr);

        node->joint->_index = boneIndex++;

        skeleton->_joints.push_back(node->joint);
        skeleton->_bone_transforms.push_back(node->joint->transform());
    }

    skeleton->_world_transforms = std::vector<Matrix>(skeleton->_bone_transforms.size());
    skeleton->_skin_transforms  = std::vector<Matrix>(skeleton->_bone_transforms.size());

    return skeleton;
}

}}}
