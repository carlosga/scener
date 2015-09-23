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
        class ModelSkin;

        /**
         * Represents bone data for a model.
         */
        class ModelBone final
        {
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
             * Gets the collection of children bones.
             */
            const std::vector<std::shared_ptr<ModelBone>>& children() const;

            /**
             * Gets the name of this bone.
             */
            const std::string& name() const;

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

        private:
            std::vector<std::shared_ptr<ModelBone>> _children   = { };
            std::string                             _name       = { };
            std::shared_ptr<ModelBone>              _parent     = { nullptr };
            SceneR::Framework::Matrix               _transform  = { SceneR::Framework::Matrix::identity };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_MODELBONE_HPP
