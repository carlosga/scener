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

class ModelBone;

/// Represents a hierarchical collection of bones.
class Skeleton final
{
public:
    /// Initializes a new instance of the Skeleton class.
    Skeleton() = default;

public:
    /// Describes how to pose the skin's geometry for use with the joints.
    /// \returns a matrix describing how to pose the skin's geometry for use with the joints.
    const SceneR::Math::Matrix& bind_shape_matrix() const noexcept;

    /// Inverse-bind matrices. Used to bring coordinates being skinned into the same space as each joint.
    /// \returns the list of matrices used to bring coordinates being skinned into the same space as each joint.
    const std::vector<SceneR::Math::Matrix>& inverse_bind_matrices() const noexcept;

    /// Returns the joints used to animate the skin.
    /// \returns the joints used to animate the skin.
    const std::vector<std::shared_ptr<ModelBone>>& joints() const noexcept;

    /// The skeleton name.
    /// \returns the name of the skeleton.
    const std::string& name() const noexcept;

    /// Gets the current bone transform matrices, relative to their parent bones.
    /// \returns the current bone transform matrices, relative to their parent bones.
    const std::vector<SceneR::Math::Matrix>& bone_transforms() const noexcept;

    /// Gets the current bone transform matrices, in absolute format.
    /// \returns the current bone transform matrices, in absolute format.
    const std::vector<SceneR::Math::Matrix>& world_transforms() const noexcept;

    /// Gets the current bone transform matrices, relative to the skinning bind pose.
    /// \returns the current bone transform matrices, relative to the skinning bind pose.
    const std::vector<SceneR::Math::Matrix>& skin_transforms() const noexcept;

    /// Advances the current animation position.
    /// \param time snapshot of the rendering timing state.
    void update(const SceneR::TimeSpan& time) noexcept;

private:
    /// Helper used by the Update method to refresh the BoneTransforms data.
    void update_bone_transforms(const SceneR::TimeSpan& time) noexcept;

    /// Helper used by the Update method to refresh the WorldTransforms data.
    void update_world_transforms() noexcept;

    /// Helper used by the Update method to refresh the SkinTransforms data.
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
