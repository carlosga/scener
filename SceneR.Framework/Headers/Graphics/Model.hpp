// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <System/IDisposable.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Content
    {
        class ModelReader;
    }
}

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class ModelBone;
        class ModelMesh;
        class SkinningData;

        /**
         * Represents a 3D model composed of multiple ModelMesh objects which may be moved independently.
         */
        class Model : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the Model class.
             */
            Model();

            /**
             * Releases all resources being used by this Model.
             */
            ~Model() override;

        public:
            void Dispose() override;

        public:
            /**
             * Copies a transform of each bone in a model relative to all parent bones of the bone into a given array.
             * @param destinationBoneTransforms The array to receive bone transforms.
             */
            void CopyAbsoluteBoneTransformsTo(std::vector<SceneR::Framework::Matrix>& destinationBoneTransforms);

            /**
             * Copies an array of transforms into each bone in the model.
             * @param sourceBoneTransforms the new bone transforms.
             */
            void CopyBoneTransformsFrom(const std::vector<SceneR::Framework::Matrix>& sourceBoneTransforms);

            /**
             * Copies each bone transform relative only to the parent bone of the model to a given array.
             * @param destinationBoneTransforms the array to receive bone transforms.
             */
            void CopyBoneTransformsTo(std::vector<SceneR::Framework::Matrix>& destinationBoneTransforms);

            /**
             * Render a model after applying the given matrix transformations.
             *
             * @param world the world matrix
             * @param view the view matrix
             * @param projection the projection matrix
             */
            void Draw(const SceneR::Framework::Matrix& world
                    , const SceneR::Framework::Matrix& view
                    , const SceneR::Framework::Matrix& projection);

            /**
             * Gets the root bone for the current model.
             */
            const std::shared_ptr<ModelBone>& Root() const;

            /**
             * Gets the collection of bones associated to the current model
             */
            const std::vector<std::shared_ptr<ModelBone>>& Bones() const;

            /**
             * Gets a collection of ModelMesh objects which composes the current model.
             */
            const std::vector<std::shared_ptr<ModelMesh>>& Meshes() const;

            /**
             * Getsthe model skinning data
             */
            const std::shared_ptr<SkinningData>& Skinning() const;

            /**
             * Gets the model tag
             */
            const System::String& Tag() const;

            /**
             * Sets the model tag
             */
            void Tag(const System::String& tag);

        private:
            std::vector<std::shared_ptr<ModelBone>> bones;
            std::vector<std::shared_ptr<ModelMesh>> meshes;
            std::shared_ptr<ModelBone>              root;
            std::shared_ptr<SkinningData>           skinning;
            System::String                          tag;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODEL_HPP */
