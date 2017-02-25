// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BONE_HPP
#define SCENER_GRAPHICS_BONE_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "scener/math/matrix.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics
{
    class animation;

    /// Represents bone data for a skeleton.
    class bone final
    {
    public:
        typedef std::size_t index_type;

    public:
        /// Initializes a new instance of the ModelBone class.
        bone() = default;

    public:
        /// Gets the index of this bone in the Bones collection.
        /// \returns the index of this bone in the Bones collection.
        index_type index() const noexcept;

        /// Gets the collection of children bones.
        /// \returns the collection of children bones.
        const std::vector<std::shared_ptr<bone>>& children() const noexcept;

        /// Gets the name of this bone.
        /// \returns the name of this bone.
        const std::string& name() const noexcept;

        /// Gets the parent of this bone.
        /// \returns the parent of this bone.
        bone* parent() const noexcept;

        /// Gets the bone animation.
        /// \returns the bone animation.
        graphics::animation* animation() const noexcept;

        /// Gets the matrix used to transform this bone relative to its parent bone.
        /// \returns the matrix used to transform this bone relative only to its parent bone.
        const scener::math::matrix4& transform() const noexcept;

        /// Sets the matrix used to transform this bone relative to its parent bone.
        /// \param transform the matrix used to transform this bone relative only to its parent bone.
        void transform(const scener::math::matrix4& transform) noexcept;

    private:
        index_type                           _index     { 0 };
        std::vector<std::shared_ptr<bone>>   _children  { };
        std::shared_ptr<bone>                _parent    { nullptr };
        std::shared_ptr<graphics::animation> _animation { nullptr };
        scener::math::matrix4                _transform { scener::math::matrix4::identity() };
        std::string                          _name      { };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_BONE_HPP
