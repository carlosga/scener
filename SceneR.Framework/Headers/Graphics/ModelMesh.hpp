// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELMESH_HPP
#define MODELMESH_HPP

#include <memory>
#include <vector>

#include <Framework/BoundingSphere.hpp>
#include <Graphics/Effect.hpp>

namespace SceneR
{
    namespace Content
    {
        class ModelReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class ModelBone;
        class ModelMeshPart;

        /**
         * Represents a mesh that is part of a Model.
         */
        class ModelMesh
        {
        public:
            /**
             * Initializes a new instance of the ModelMesh class.
             */
            ModelMesh();

            /**
             * Releases all resources being used by this ModelMesh.
             */
            ~ModelMesh();

        public:
            const SceneR::Framework::BoundingSphere& BoundingSphere() const;

            /**
             * Draws all of the ModelMeshPart objects in this mesh.
             */
            void Draw();

            /**
             * Gets the list of efects of each mesh part.
             */
            std::vector<std::shared_ptr<Effect>> Effects() const;

            /**
             * Gets the ModelMeshPart objects that make up this mesh.
             * Each part of a mesh is composed of a set of primitives that share the same material.
             */
            const std::vector<std::shared_ptr<ModelMeshPart>>& MeshParts() const;

            /**
             * Gets the model mesh name
             */
            const std::u16string& Name() const;

            /**
             * Sets the model mesh name
             */
            void Name(const std::u16string& name);

            /**
             * Gets the parent bone for this mesh. The parent bone of a mesh contains a
             * transformation matrix that describes how the mesh is located relative to
             * any parent meshes in a model.
             */
            const std::shared_ptr<ModelBone>& ParentBone() const;

            /**
             * Gets the model mesh tag
             */
            const std::u16string& Tag() const;

            /**
             * Sets the model mesh tag
             */
            void Tag(const std::u16string& tag);

        private:
            SceneR::Framework::BoundingSphere           boundingSphere;
            std::vector<std::shared_ptr<ModelMeshPart>> meshParts;
            std::u16string                              name;
            std::shared_ptr<ModelBone>                  parentBone;
            std::u16string                              tag;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESH_HPP */
