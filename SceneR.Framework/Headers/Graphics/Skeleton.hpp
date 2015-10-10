// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_INSTANCESKIN_HPP
#define GRAPHICS_INSTANCESKIN_HPP

#include <memory>
#include <string>
#include <vector>

#include <Framework/Matrix.hpp>

namespace System
{
    struct TimeSpan;
}

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class ModelMesh;
        class ModelBone;

        class Skeleton final
        {
        public:
            Skeleton() = default;
            ~Skeleton() = default;

        public:
            /**
             * Describes how to pose the skin's geometry for use with the joints.
             * Floating-point 4x4 transformation matrix stored in column-major order.
             */
            const SceneR::Framework::Matrix& bind_shape_matrix() const noexcept;

            /**
             * Inverse-bind matrices. Used to bring coordinates being skinned into the same space as each joint.
             */
            const std::vector<SceneR::Framework::Matrix>& inverse_bind_matrices() const noexcept;

            /**
             * Joints used to animate the skin.
             */
            const std::vector<std::shared_ptr<ModelBone>>& joints() const noexcept;

            /**
             * The skeleton name.
             */
            const std::string& name() const noexcept;

            /**
             * Gets the current bone transform matrices, relative to their parent bones.
             */
            const std::vector<SceneR::Framework::Matrix>& bone_transforms() const noexcept;

            /**
             * Gets the current bone transform matrices, in absolute format.
             */
            const std::vector<SceneR::Framework::Matrix>& world_transforms() const noexcept;

            /**
             * Gets the current bone transform matrices, relative to the skinning bind pose.
             */
            const std::vector<SceneR::Framework::Matrix>& skin_transforms() const noexcept;

            /**
             * Advances the current animation position.
             */
            void update(const System::TimeSpan&          time
                      , const bool&                      relativeToCurrentTime
                      , const SceneR::Framework::Matrix& rootTransform) noexcept;

        private:
            /**
             * Helper used by the Update method to refresh the BoneTransforms data.
             */
            void update_bone_transforms(const System::TimeSpan& time, const bool& relativeToCurrentTime) noexcept;

            /**
             * Helper used by the Update method to refresh the WorldTransforms data.
             */
            void update_world_transforms(const SceneR::Framework::Matrix& rootTransform) noexcept;

            /**
             * Helper used by the Update method to refresh the SkinTransforms data.
             */
            void update_skin_transforms() noexcept;

        private:
            SceneR::Framework::Matrix               _bind_shape_matrix     { SceneR::Framework::Matrix::identity };
            std::vector<SceneR::Framework::Matrix>  _inverse_bind_matrices { };
            std::vector<std::shared_ptr<ModelBone>> _joints                { };
            std::string                             _name                  { };

            std::vector<SceneR::Framework::Matrix> _bone_transforms;
            std::vector<SceneR::Framework::Matrix> _world_transforms;
            std::vector<SceneR::Framework::Matrix> _skin_transforms;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_INSTANCESKIN_HPP