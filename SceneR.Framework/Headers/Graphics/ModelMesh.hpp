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
        class MeshesReader;
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
            /**
             * Gets the BoundingSphere that contains this mesh.
             * @return The BoundingSphere that contains this mesh.
             */
            const SceneR::Framework::BoundingSphere& bounding_sphere() const;

            /**
             * Gets the name of this mesh.
             * @return The name of this mesh.
             */
            const std::u16string& name() const;

            /**
             * Gets the list of efects of each mesh part.
             */
            std::vector<std::shared_ptr<Effect>> effects() const;

            /**
             * Gets the ModelMeshPart objects that make up this mesh.
             * Each part of a mesh is composed of a set of primitives that share the same material.
             */
            const std::vector<std::shared_ptr<ModelMeshPart>>& mesh_parts() const;

            /**
             * Gets the parent bone for this mesh. The parent bone of a mesh contains a
             * transformation matrix that describes how the mesh is located relative to
             * any parent meshes in a model.
             */
            const std::shared_ptr<ModelBone>& parent_bone() const;

        public:
            /**
             * Draws all of the ModelMeshPart objects in this mesh.
             */
            void draw();

        public:
            std::u16string tag;

        private:
            std::u16string                              _name;
            std::vector<std::shared_ptr<ModelMeshPart>> _mesh_parts;
            std::shared_ptr<ModelBone>                  _parent_bone;
            SceneR::Framework::BoundingSphere           _bounding_sphere;

            friend class SceneR::Content::MeshesReader;
            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESH_HPP */
