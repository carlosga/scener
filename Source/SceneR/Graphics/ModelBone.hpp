// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_MODELBONE_HPP
#define SCENER_GRAPHICS_MODELBONE_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "SceneR/Math/Matrix.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics {

class Animation;

/// Represents bone data for a skeleton.
class ModelBone final
{
public:
    typedef std::size_t index_type;

public:
    /// Initializes a new instance of the ModelBone class.
    ModelBone() = default;

public:
    /// Gets the index of this bone in the Bones collection.
    /// \returns the index of this bone in the Bones collection.
    index_type index() const noexcept;

    /// Gets the collection of children bones.
    /// \returns the collection of children bones.
    const std::vector<std::shared_ptr<ModelBone>>& children() const noexcept;

    /// Gets the name of this bone.
    /// \returns the name of this bone.
    const std::string& name() const noexcept;

    /// Gets the parent of this bone.
    /// \returns the parent of this bone.
    ModelBone* parent() const noexcept;

    /// Gets the bone animation.
    /// \returns the bone animation.
    Animation* animation() const noexcept;

    /// Gets the matrix used to transform this bone relative to its parent bone.
    /// \returns the matrix used to transform this bone relative only to its parent bone.
    const SceneR::Math::Matrix& transform() const noexcept;

    /// Sets the matrix used to transform this bone relative to its parent bone.
    /// \param transform the matrix used to transform this bone relative only to its parent bone.
    void transform(const SceneR::Math::Matrix& transform) noexcept;

private:
    index_type                              _index     { 0 };
    std::vector<std::shared_ptr<ModelBone>> _children  { };
    std::shared_ptr<ModelBone>              _parent    { nullptr };
    std::shared_ptr<Animation>              _animation { nullptr };
    SceneR::Math::Matrix                    _transform { SceneR::Math::Matrix::identity };
    std::string                             _name      { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_MODELBONE_HPP
