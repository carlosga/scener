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
            ModelSkin() = default;

            ~ModelSkin() = default;

        public:
            /**
             * Describes how to pose the skin's geometry for use with the joints.
             * Floating-point 4x4 transformation matrix stored in column-major order.
             */
            const SceneR::Framework::Matrix& bindShapeMatrix() const;

            /**
             * Inverse-bind matrices. Used to bring coordinates being skinned into the same space as each joint
             */
            const std::vector<SceneR::Framework::Matrix>& inverseBindMatrices() const;

            /**
             * Joints used to animate the skin
             */
            const std::vector<std::shared_ptr<ModelBone>>& joints() const;

            /**
             * The skin name.
             */
            const std::string& name() const;

            /**
             * Contains one or more skeletons, each of which is the root of a node hierarchy.
             */
            const std::vector<std::shared_ptr<ModelBone>>& skeletons() const;

        private:
            SceneR::Framework::Matrix               _bindShapeMatrix     = { SceneR::Framework::Matrix::identity };
            std::vector<SceneR::Framework::Matrix>  _inverseBindMatrices = { };
            std::vector<std::shared_ptr<ModelBone>> _joints              = { };
            std::string                             _name                = { };
            std::vector<std::shared_ptr<ModelBone>> _skeletons           = { };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_INSTANCESKIN_HPP
