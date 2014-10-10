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

#ifndef MODELBONE_HPP
#define MODELBONE_HPP

#include <memory>
#include <vector>

#include <Framework/Matrix.hpp>
#include <System/Core.hpp>

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
        /**
         * Represents bone data for a model.
         */
        class ModelBone
        {
        public:
            /**
             * Initializes a new instance of the ModelBone class.
             */
            ModelBone();

            /**
             * Releases all resources being used by this ModelBone.
             */
            ~ModelBone() = default;

        public:
            /**
             * Gets the collection of children bones.
             */
            const std::vector<std::shared_ptr<ModelBone>>& Children() const;

            /**
             * Gets the index of this bone in the Bones collection.
             */
            const System::Size& Index() const;

            /**
             * Gets the bone name
             */
            const System::String& Name() const;

            /**
             * Gets the bone name
             */
            void Name(const System::String& name);

            /**
             * Gets the parent of the current bone
             */
            const std::shared_ptr<ModelBone>& Parent() const;

            /**
             * Gets the matrix used to transform this bone relative to its parent bone.
             */
            const SceneR::Framework::Matrix& Transform() const;

            /**
             * Sets the matrix used to transform this bone relative to its parent bone.
             */
            void Transform(const SceneR::Framework::Matrix& transform);

        private:
            std::vector<std::shared_ptr<ModelBone>> children;
            System::Size                            index;
            System::String                          name;
            std::shared_ptr<ModelBone>              parent;
            SceneR::Framework::Matrix               transform;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELBONE_HPP */
