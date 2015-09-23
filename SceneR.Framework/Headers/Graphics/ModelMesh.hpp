// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_MODELMESH_HPP
#define GRAPHICS_MODELMESH_HPP

#include <memory>
#include <vector>
#include <string>

#include <Framework/BoundingSphere.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class EffectTechnique;
        class ModelSkin;
        class ModelBone;
        class ModelMeshPart;

        /**
         * Represents a mesh that is part of a Model.
         */
        class ModelMesh final
        {
        public:
            /**
             * Initializes a new instance of the ModelMesh class.
             */
            ModelMesh() = default;

            /**
             * Releases all resources being used by this ModelMesh.
             */
            ~ModelMesh() = default;

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
            const std::string& name() const;

            /**
             * Gets the list of efects of each mesh part.
             */
            std::vector<std::shared_ptr<EffectTechnique>> effects() const;

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

            /**
             * Joints and matrices defining a skin.
             */
            ModelSkin* skin() const;

        public:
            /**
             * Draws all of the ModelMeshPart objects in this mesh.
             */
            void draw();

        private:
            std::string                                 _name            = { };
            std::vector<std::shared_ptr<ModelMeshPart>> _mesh_parts      = { };
            std::shared_ptr<ModelBone>                  _parent_bone     = { nullptr };
            SceneR::Framework::BoundingSphere           _bounding_sphere = { SceneR::Framework::Vector3::zero, 0.0f };
            std::shared_ptr<ModelSkin>                  _skin            = { nullptr };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_MODELMESH_HPP
