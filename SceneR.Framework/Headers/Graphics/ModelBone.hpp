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
    namespace Graphics
    {
        /**
         * Represents bone data for a model.
         */
        class ModelBone final
        {
        public:
            /**
             * Initializes a new instance of the ModelBone class.
             */
            ModelBone();

            /**
             * Releases all resources being used by this ModelBone.
             */
            ~ModelBone();

        public:
            /**
             * Gets the collection of children bones.
             */
            const std::vector<std::shared_ptr<ModelBone>>& children() const;

            /**
             * Gets the index of this bone in the Bones collection.
             */
            std::uint32_t index() const;

            /**
             * Gets the parent of the current bone
             */
            const std::shared_ptr<ModelBone>& parent() const;

            /**
             * Gets the matrix used to transform this bone relative to its parent bone.
             */
            const SceneR::Framework::Matrix& transform() const;

            /**
             * Sets the matrix used to transform this bone relative to its parent bone.
             */
            void transform(const SceneR::Framework::Matrix& transform);

        public:
            /**
             * Gets or sets the bone name
             */
            std::string name;

        private:
            std::vector<std::shared_ptr<ModelBone>> _children;
            std::uint32_t                           _index;
            std::shared_ptr<ModelBone>              _parent;
            SceneR::Framework::Matrix               _transform;
        };
    }
}

#endif  // GRAPHICS_MODELBONE_HPP
