// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/skeleton_reader.hpp"

#include <vector>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/skeleton.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::math::matrix4;
    using scener::graphics::skeleton;
    using namespace scener::content::gltf;

    auto content_type_reader<skeleton>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<skeleton>();
        auto accessor = input->read_object<gltf::accessor>(value[k_inverse_bind_matrices].get<std::string>());

        // Name
        instance->_name = key;

        // Bind shape matrix
        instance->_bind_shape_matrix = input->convert<matrix4>(value[k_bind_shape_matrix].get<json::array_t>());

        // Inverse bind matrices
        instance->_inverse_bind_matrices.reserve(accessor->attribute_count());

        for (std::uint32_t i = 0; i < accessor->attribute_count(); ++i)
        {
            instance->_inverse_bind_matrices.push_back(accessor->get_element<matrix4>(i));
        }

        // Joints
        const auto& joint_names = value[k_joint_names].get<std::vector<std::string>>();
        const auto  joint_count = joint_names.size();
        auto        bone_index  = std::uint32_t { 0 };

        instance->_bones.reserve(joint_count);
        instance->_bone_transforms.reserve(joint_count);

        for (const auto& name : joint_names)
        {
            auto node = input->read_object<gltf::node>(name); 

            node->joint->_index = bone_index++;

            instance->_bones.push_back(node->joint);
            instance->_bone_transforms.push_back(node->joint->transform());
        }

        instance->_world_transforms = std::vector<matrix4>(instance->_bone_transforms.size());
        instance->_skin_transforms  = std::vector<matrix4>(instance->_bone_transforms.size());

        return instance;
    }
}
