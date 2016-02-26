// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SKELETON_HPP
#define SCENER_GRAPHICS_SKELETON_HPP

#include <memory>
#include <string>
#include <vector>

#include "scener/math/matrix.hpp"

namespace scener { class timespan; }

namespace scener { namespace content { namespace readers { template <typename T> class content_type_reader; } } }

namespace scener { namespace graphics {

class bone;

/// Represents a hierarchical collection of bones.
class skeleton final
{
public:
    /// Initializes a new instance of the Skeleton class.
    skeleton() = default;

public:
    /// Describes how to pose the skin's geometry for use with the bones.
    /// \returns a matrix describing how to pose the skin's geometry for use with the bones.
    const scener::math::matrix4& bind_shape_matrix() const noexcept;

    /// Inverse-bind matrices. Used to bring coordinates being skinned into the same space as each bone.
    /// \returns the list of matrices used to bring coordinates being skinned into the same space as each bone.
    const std::vector<scener::math::matrix4>& inverse_bind_matrices() const noexcept;

    /// Returns the bones used to animate the skin.
    /// \returns the bones used to animate the skin.
    const std::vector<std::shared_ptr<bone>>& bones() const noexcept;

    /// The skeleton name.
    /// \returns the name of the skeleton.
    const std::string& name() const noexcept;

    /// Gets the current bone transform matrices, relative to their parent bones.
    /// \returns the current bone transform matrices, relative to their parent bones.
    const std::vector<scener::math::matrix4>& bone_transforms() const noexcept;

    /// Gets the current bone transform matrices, in absolute format.
    /// \returns the current bone transform matrices, in absolute format.
    const std::vector<scener::math::matrix4>& world_transforms() const noexcept;

    /// Gets the current bone transform matrices, relative to the skinning bind pose.
    /// \returns the current bone transform matrices, relative to the skinning bind pose.
    const std::vector<scener::math::matrix4>& skin_transforms() const noexcept;

    /// Advances the current animation position.
    /// \param time snapshot of the rendering timing state.
    void update(const scener::timespan& time) noexcept;

private:
    /// Helper used by the Update method to refresh the BoneTransforms data.
    void update_bone_transforms(const scener::timespan& time) noexcept;

    /// Helper used by the Update method to refresh the WorldTransforms data.
    void update_world_transforms() noexcept;

    /// Helper used by the Update method to refresh the SkinTransforms data.
    void update_skin_transforms() noexcept;

private:
    scener::math::matrix4              _bind_shape_matrix     { scener::math::matrix4::identity() };
    std::vector<scener::math::matrix4> _inverse_bind_matrices { };
    std::vector<std::shared_ptr<bone>> _bones                 { };
    std::vector<scener::math::matrix4> _bone_transforms       { };
    std::vector<scener::math::matrix4> _world_transforms      { };
    std::vector<scener::math::matrix4> _skin_transforms       { };
    std::string                        _name                  { };

    template <typename T> friend class scener::content::readers::content_type_reader;
};

}}

#endif // SCENER_GRAPHICS_SKELETON_HPP
