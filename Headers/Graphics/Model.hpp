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

#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <string>
#include <vector>
#include "Core/Matrix.hpp"
#include "Content/Readers/ModelReader.hpp"
#include "Graphics/ModelBone.hpp"
#include "Graphics/ModelMesh.hpp"

namespace SceneR
{
	namespace Graphics
	{
		/**
		 * Represents a 3D model composed of multiple ModelMesh objects which may be moved independently.
		 */
		class Model
		{
		public:
			/**
			 * Initializes a new instance of the Model class.
			 */
			Model();
			
		public:
            /**
             * Render a model after applying the matrix transformations.
             */
            void Draw(const SceneR::Core::Matrix& world,
                      const SceneR::Core::Matrix& view,
                      const SceneR::Core::Matrix& projection);

			/**
			 * Gets the root bone for the current model.
			 */
			const std::shared_ptr<ModelBone> Root() const;
			
			/**
			 * Gets the collection of bones associated to the current model
			 */
			const std::vector<std::shared_ptr<ModelBone>>& Bones() const;
			
			/**
			 * Gets a collection of ModelMesh objects which composes the current model.
			 */
			const std::vector<std::shared_ptr<ModelMesh>>& Meshes() const;

			/**
			 * Gets the model tag
			 */
			const std::wstring& GetTag() const;

            /**
             * Sets the model tag
             */
            void SetTag(const std::wstring& tag);

		private:
			std::vector<std::shared_ptr<ModelBone>> bones;
			std::vector<std::shared_ptr<ModelMesh>> meshes;
			std::shared_ptr<ModelBone> 			    root;
			std::wstring                            tag;
			
			friend class SceneR::Content::ModelReader;
		};
	}
}

#endif 	// MODEL_HPP
