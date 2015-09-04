// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODEL_HPP
#define MODEL_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Content
    {
        class AccessorsReader;
        class BuffersReader;
        class BufferViewsReader;
        class MaterialsReader;
        class MeshesReader;
        class ModelReader;
        class TechniquesReader;
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
        class Accessor;
        class Buffer;
        class BufferView;
        class Effect;
        class Material;
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
            const std::map<std::string, std::shared_ptr<ModelMesh>>& Meshes() const;

            /**
             * Gets the model skinning data
             */
            // const std::shared_ptr<SkinningData>& Skinning() const;

            /**
             * Gets the model tag
             */
            const std::u16string& Tag() const;

            /**
             * Sets the model tag
             */
            void Tag(const std::u16string& tag);

        private:
            // std::shared_ptr<SkinningData>           skinning;

            std::u16string                                     tag;
            std::vector<std::shared_ptr<ModelBone>>            bones;
            std::shared_ptr<ModelBone>                         root;
            std::map<std::string, std::shared_ptr<ModelMesh>>  meshes;
            std::map<std::string, std::shared_ptr<Buffer>>     buffers;
            std::map<std::string, std::shared_ptr<BufferView>> bufferViews;
            std::map<std::string, std::shared_ptr<Accessor>>   accessors;
            std::map<std::string, std::shared_ptr<Effect>>     techniques;
            std::map<std::string, std::shared_ptr<Material>>   materials;

            friend class SceneR::Content::AccessorsReader;
            friend class SceneR::Content::BuffersReader;
            friend class SceneR::Content::BufferViewsReader;
            friend class SceneR::Content::MaterialsReader;
            friend class SceneR::Content::MeshesReader;
            friend class SceneR::Content::ModelReader;
            friend class SceneR::Content::TechniquesReader;
        };
    }
}

#endif  /* MODEL_HPP */
