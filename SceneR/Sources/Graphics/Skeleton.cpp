// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Skeleton.hpp>

#include <algorithm>

#include <Framework/Matrix.hpp>
#include <Graphics/Animation.hpp>
#include <Graphics/Keyframe.hpp>
#include <Graphics/ModelBone.hpp>
#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using System::TimeSpan;

        const Matrix& Skeleton::bind_shape_matrix() const noexcept
        {
            return _bind_shape_matrix;
        }

        const std::vector<Matrix>& Skeleton::inverse_bind_matrices() const noexcept
        {
            return _inverse_bind_matrices;
        }

        const std::vector<std::shared_ptr<ModelBone>>& Skeleton::joints() const noexcept
        {
            return _joints;
        }

        const std::string& Skeleton::name() const noexcept
        {
            return _name;
        }

        const std::vector<Matrix>& Skeleton::bone_transforms() const noexcept
        {
            return _bone_transforms;
        }

        const std::vector<Matrix>& Skeleton::world_transforms() const noexcept
        {
            return _world_transforms;
        }

        const std::vector<Matrix>& Skeleton::skin_transforms() const noexcept
        {
            return _skin_transforms;
        }

        void Skeleton::update(const TimeSpan& time, const bool& relativeToCurrentTime, const Matrix& rootTransform) noexcept
        {
            this->update_bone_transforms(time, relativeToCurrentTime);
            this->update_world_transforms(rootTransform);
            this->update_skin_transforms();
        }

        void Skeleton::update_bone_transforms(const TimeSpan& time, const bool& relativeToCurrentTime) noexcept
        {
            for (const auto joint : _joints)
            {
                joint->animation()->update(time, relativeToCurrentTime);

                // Use this keyframe.
                _bone_transforms[joint->index()] = joint->animation()->current_keyframe().transform();
            }
        }

        void Skeleton::update_world_transforms(const Matrix& rootTransform) noexcept
        {
            // Root bone.
            _world_transforms[0] = _bone_transforms[0] * rootTransform;

            // Child bones.
            for (std::size_t bone = 1; bone < _world_transforms.size(); ++bone)
            {
                auto parentBone = _joints[bone]->parent()->index();

                _world_transforms[bone] = _bone_transforms[bone] * _world_transforms[parentBone];
            }
        }

        void Skeleton::update_skin_transforms() noexcept
        {
            for (std::size_t bone = 0; bone < _skin_transforms.size(); ++bone)
            {
                _skin_transforms[bone] = _bind_shape_matrix * _inverse_bind_matrices[bone] * _world_transforms[bone];
            }
        }
    }
}
