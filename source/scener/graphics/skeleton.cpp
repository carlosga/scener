// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/skeleton.hpp"

#include "scener/graphics/animation.hpp"
#include "scener/graphics/bone.hpp"

namespace scener { namespace graphics {

using scener::timespan;
using scener::math::matrix4;

const matrix4& skeleton::bind_shape_matrix() const noexcept
{
    return _bind_shape_matrix;
}

const std::vector<matrix4>& skeleton::inverse_bind_matrices() const noexcept
{
    return _inverse_bind_matrices;
}

const std::vector<std::shared_ptr<bone>>& skeleton::bones() const noexcept
{
    return _bones;
}

const std::string& skeleton::name() const noexcept
{
    return _name;
}

const std::vector<matrix4>& skeleton::bone_transforms() const noexcept
{
    return _bone_transforms;
}

const std::vector<matrix4>& skeleton::world_transforms() const noexcept
{
    return _world_transforms;
}

const std::vector<matrix4>& skeleton::skin_transforms() const noexcept
{
    return _skin_transforms;
}

void skeleton::update(const timespan& time) noexcept
{
    this->update_bone_transforms(time);
    this->update_world_transforms();
    this->update_skin_transforms();
}

void skeleton::update_bone_transforms(const timespan& time) noexcept
{
    std::for_each(_bones.begin(), _bones.end(), [&](const auto& bone) -> void
    {
        bone->animation()->update(time, true);

        // Use this keyframe.
        _bone_transforms[bone->index()] = bone->animation()->current_keyframe().transform();
    });
}

void skeleton::update_world_transforms() noexcept
{
//    const auto count = _bones.size();

    // Root bone.
    _world_transforms[0] = _bone_transforms[0];

    // Child bones.
//    for (std::size_t bone = 1; bone < count; ++bone)
//    {
//        const auto parentBone = _bones[bone]->parent()->index();

//        _world_transforms[bone] = _bone_transforms[bone] * _world_transforms[parentBone];
//    }

    std::for_each(_bones.begin() + 1, _bones.end(), [&](const auto& bone) -> void
    {
        const auto parent_bone = bone->parent()->index();
        const auto bone_index = bone->index();

        _world_transforms[bone_index] = _bone_transforms[bone_index] * _world_transforms[parent_bone];
    });
}

void skeleton::update_skin_transforms() noexcept
{
    std::for_each(_bones.begin(), _bones.end(), [&](const auto& bone) -> void
    {
        const auto bone_index = bone->index();

        _skin_transforms[bone_index] = _bind_shape_matrix * _inverse_bind_matrices[bone_index] * _world_transforms[bone_index];
    });
}

}}
