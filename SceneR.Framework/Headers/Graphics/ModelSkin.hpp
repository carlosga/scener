// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_INSTANCESKIN_HPP
#define GRAPHICS_INSTANCESKIN_HPP

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
        class ModelMesh;
        class ModelBone;
        class Node;

        class ModelSkin final
        {
        public:
            ModelSkin();
            ~ModelSkin();

        public:
            /**
             * Floating-point 4x4 transformation matrix stored in column-major order.
             */
            const SceneR::Framework::Matrix& bindShapeMatrix() const;

            /**
             * Inverse-bind matrices.
             */
            const std::vector<SceneR::Framework::Matrix>& inverseBindMatrices() const;

            /**
             * Joints if this skin.
             */
            const std::vector<std::shared_ptr<ModelBone>>& joints() const;

            /**
             * The id (JSON property name) of the skin referenced by this node.
             */
            const std::string& name() const;

        private:
            SceneR::Framework::Matrix               _bindShapeMatrix;
            std::vector<SceneR::Framework::Matrix>  _inverseBindMatrices;
            std::vector<std::shared_ptr<ModelBone>> _joints;
            std::string                             _name;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_INSTANCESKIN_HPP
