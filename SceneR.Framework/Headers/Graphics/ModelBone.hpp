// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_MODELBONE_HPP
#define GRAPHICS_MODELBONE_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class Skeleton;

        /**
         * Represents bone data for a model.
         */
        class ModelBone final
        {
        public:
            typedef std::size_t index_type;

        public:
            /**
             * Initializes a new instance of the ModelBone class.
             */
            ModelBone() = default;

            /**
             * Releases all resources being used by this ModelBone.
             */
            ~ModelBone() = default;

        public:
            /**
             * Gets the index of this bone in the Bones collection.
             */
            index_type index() const noexcept;

            /**
             * Gets the collection of children bones.
             */
            const std::vector<std::shared_ptr<ModelBone>>& children() const noexcept;

            /**
             * Gets the name of this bone.
             */
            const std::string& name() const noexcept;

            /**
             * Gets the parent of the current bone
             */
            ModelBone* parent() const noexcept;

            /**
             * Gets the matrix used to transform this bone relative to its parent bone.
             */
            const SceneR::Framework::Matrix& transform() const noexcept;

            /**
             * Sets the matrix used to transform this bone relative to its parent bone.
             */
            void transform(const SceneR::Framework::Matrix& transform) noexcept;

        private:
            index_type                              _index     { 0 };
            std::vector<std::shared_ptr<ModelBone>> _children  { };
            std::string                             _name      { };
            std::shared_ptr<ModelBone>              _parent    { nullptr };
            SceneR::Framework::Matrix               _transform { SceneR::Framework::Matrix::identity };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_MODELBONE_HPP