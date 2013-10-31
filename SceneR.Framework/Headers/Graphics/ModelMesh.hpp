//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef MODELMESH_HPP
#define MODELMESH_HPP

#include <Graphics/Effect.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <string>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
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
             * Draws all of the ModelMeshPart objects in this mesh.
             */
            void Draw();

            /**
             * Gets the list of efects of each mesh part.
             */
            const std::vector<std::shared_ptr<Effect>> GetEffects();

            /**
             * Gets the ModelMeshPart objects that make up this mesh.
             * Each part of a mesh is composed of a set of primitives that share the same material.
             */
            const std::vector<std::shared_ptr<ModelMeshPart>>& MeshParts() const;

            /**
             * Gets the model mesh name
             */
            const std::wstring& GetName() const;

            /**
             * Sets the model mesh name
             */
            void SetName(const std::wstring& name);

            /**
             * Gets the parent bone for this mesh. The parent bone of a mesh contains a
             * transformation matrix that describes how the mesh is located relative to
             * any parent meshes in a model.
             */
            std::shared_ptr<ModelBone> ParentBone() const;

            /**
             * Gets the model mesh tag
             */
            const std::wstring& GetTag() const;

            /**
             * Sets the model mesh tag
             */
            void SetTag(const std::wstring& tag);

        private:
            std::vector<std::shared_ptr<ModelMeshPart>> meshParts;
            std::wstring                                name;
            std::shared_ptr<ModelBone>                  parentBone;
            std::wstring                                tag;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESH_HPP */
