// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <string>
#include <vector>

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Content
    {
        class MeshesReader;
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
            ~Model();

        public:
            void dispose() override;

        public:
            /**
             * Gets the model name.
             * @return the model name.
             */
            const std::u16string name() const;

            /**
             * Copies a transform of each bone in a model relative to all parent bones of the bone into a given array.
             * @param destinationBoneTransforms The array to receive bone transforms.
             */
            void copy_absolute_bone_transforms_to(std::vector<SceneR::Framework::Matrix>& destinationBoneTransforms);

            /**
             * Copies an array of transforms into each bone in the model.
             * @param sourceBoneTransforms the new bone transforms.
             */
            void copy_bone_transforms_from(const std::vector<SceneR::Framework::Matrix>& sourceBoneTransforms);

            /**
             * Copies each bone transform relative only to the parent bone of the model to a given array.
             * @param destinationBoneTransforms the array to receive bone transforms.
             */
            void copy_bone_transforms_to(std::vector<SceneR::Framework::Matrix>& destinationBoneTransforms);

            /**
             * Gets the root bone for the current model.
             */
            const std::shared_ptr<ModelBone>& root() const;

            /**
             * Gets the collection of bones associated to the current model
             */
            const std::vector<std::shared_ptr<ModelBone>>& bones() const;

            /**
             * Gets a collection of ModelMesh objects which composes the current model.
             */
            const std::vector<std::shared_ptr<ModelMesh>>& meshes() const;

            /**
             * Render a model after applying the given matrix transformations.
             *
             * @param world the world matrix
             * @param view the view matrix
             * @param projection the projection matrix
             */
            void draw(const SceneR::Framework::Matrix& world
                    , const SceneR::Framework::Matrix& view
                    , const SceneR::Framework::Matrix& projection);

        private:
            std::u16string                           _name;
            std::vector<std::shared_ptr<ModelBone>>  _bones;
            std::shared_ptr<ModelBone>               _root;
            std::vector<std::shared_ptr<ModelMesh>>  _meshes;

            friend class SceneR::Content::MeshesReader;
        };
    }
}

#endif  /* MODEL_HPP */
