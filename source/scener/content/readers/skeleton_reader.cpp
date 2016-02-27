// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/skeleton_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/graphics/Skeleton.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::math::matrix4;

auto content_type_reader<graphics::skeleton>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto skeleton = std::make_shared<graphics::skeleton>();
    auto accessor = input->read_object<gltf::accessor>(source["inverseBindMatrices"].string_value());

    // Name
    skeleton->_name = key;

    // Bind shape matrix
    skeleton->_bind_shape_matrix = input->convert<matrix4>(source["bindShapeMatrix"].array_items());

    // Inverse bind matrices
    skeleton->_inverse_bind_matrices.reserve(accessor->attribute_count());

    for (std::size_t i = 0; i < accessor->attribute_count(); ++i)
    {
        skeleton->_inverse_bind_matrices.push_back(accessor->get_element<matrix4>(i));
    }

    // Joints
    const auto& joint_names = source["jointNames"].array_items();
    const auto  joint_count = joint_names.size();
    auto        bone_index  = std::size_t { 0 };

    skeleton->_bones.reserve(joint_count);
    skeleton->_bone_transforms.reserve(joint_count);

    for (const auto& name : joint_names)
    {
        auto node = input->find_joint_node(name.string_value());

        Ensures(node.get() != nullptr && node->joint.get() != nullptr);

        node->joint->_index = bone_index++;

        skeleton->_bones.push_back(node->joint);
        skeleton->_bone_transforms.push_back(node->joint->transform());
    }

    skeleton->_world_transforms = std::vector<matrix4>(skeleton->_bone_transforms.size());
    skeleton->_skin_transforms  = std::vector<matrix4>(skeleton->_bone_transforms.size());

    return skeleton;
}

}}}
