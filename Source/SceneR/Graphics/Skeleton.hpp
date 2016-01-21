// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SKELETON_HPP
#define SCENER_GRAPHICS_SKELETON_HPP

#include <memory>
#include <string>
#include <vector>

#include "SceneR/Math/Matrix.hpp"

namespace SceneR { struct TimeSpan; }

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

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
    const SceneR::Math::Matrix& bind_shape_matrix() const noexcept;

    /**
     * Inverse-bind matrices. Used to bring coordinates being skinned into the same space as each joint.
     */
    const std::vector<SceneR::Math::Matrix>& inverse_bind_matrices() const noexcept;

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
    const std::vector<SceneR::Math::Matrix>& bone_transforms() const noexcept;

    /**
     * Gets the current bone transform matrices, in absolute format.
     */
    const std::vector<SceneR::Math::Matrix>& world_transforms() const noexcept;

    /**
     * Gets the current bone transform matrices, relative to the skinning bind pose.
     */
    const std::vector<SceneR::Math::Matrix>& skin_transforms() const noexcept;

    /**
     * Advances the current animation position.
     */
    void update(const SceneR::TimeSpan&     time
              , bool                        relativeToCurrentTime
              , const SceneR::Math::Matrix& rootTransform) noexcept;

private:
    /**
     * Helper used by the Update method to refresh the BoneTransforms data.
     */
    void update_bone_transforms(const SceneR::TimeSpan& time, bool relativeToCurrentTime) noexcept;

    /**
     * Helper used by the Update method to refresh the WorldTransforms data.
     */
    void update_world_transforms(const SceneR::Math::Matrix& rootTransform) noexcept;

    /**
     * Helper used by the Update method to refresh the SkinTransforms data.
     */
    void update_skin_transforms() noexcept;

private:
    SceneR::Math::Matrix                    _bind_shape_matrix     { SceneR::Math::Matrix::identity };
    std::vector<SceneR::Math::Matrix>       _inverse_bind_matrices { };
    std::vector<std::shared_ptr<ModelBone>> _joints                { };
    std::vector<SceneR::Math::Matrix>       _bone_transforms       { };
    std::vector<SceneR::Math::Matrix>       _world_transforms      { };
    std::vector<SceneR::Math::Matrix>       _skin_transforms       { };
    std::string                             _name                  { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_SKELETON_HPP
