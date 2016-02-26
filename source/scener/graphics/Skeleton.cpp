// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/Skeleton.hpp"

#include "scener/graphics/Animation.hpp"
#include "scener/graphics/Bone.hpp"

namespace scener { namespace graphics {

using scener::time_span;
using scener::math::matrix4;

const matrix4& Skeleton::bind_shape_matrix() const noexcept
{
    return _bind_shape_matrix;
}

const std::vector<matrix4>& Skeleton::inverse_bind_matrices() const noexcept
{
    return _inverse_bind_matrices;
}

const std::vector<std::shared_ptr<Bone>>& Skeleton::bones() const noexcept
{
    return _bones;
}

const std::string& Skeleton::name() const noexcept
{
    return _name;
}

const std::vector<matrix4>& Skeleton::bone_transforms() const noexcept
{
    return _bone_transforms;
}

const std::vector<matrix4>& Skeleton::world_transforms() const noexcept
{
    return _world_transforms;
}

const std::vector<matrix4>& Skeleton::skin_transforms() const noexcept
{
    return _skin_transforms;
}

void Skeleton::update(const time_span& time) noexcept
{
    this->update_bone_transforms(time);
    this->update_world_transforms();
    this->update_skin_transforms();
}

void Skeleton::update_bone_transforms(const time_span& time) noexcept
{
    for (const auto& joint : _bones)
    {
        joint->animation()->update(time, true);

        // Use this keyframe.
        _bone_transforms[joint->index()] = joint->animation()->current_keyframe().transform();
    }
}

void Skeleton::update_world_transforms() noexcept
{
    const auto count = _bones.size();

    // Root bone.
    _world_transforms[0] = _bone_transforms[0];

    // Child bones.
    for (std::size_t bone = 1; bone < count; ++bone)
    {
        const auto parentBone = _bones[bone]->parent()->index();

        _world_transforms[bone] = _bone_transforms[bone] * _world_transforms[parentBone];
    }
}

void Skeleton::update_skin_transforms() noexcept
{
    const auto count = _bones.size();

    for (std::size_t bone = 0; bone < count; ++bone)
    {
        _skin_transforms[bone] = _bind_shape_matrix * _inverse_bind_matrices[bone] * _world_transforms[bone];
    }
}

}}
