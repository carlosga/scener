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

#ifndef GRAPHICSRESOURCEMANAGER_HPP
#define GRAPHICSRESOURCEMANAGER_HPP

#include <memory>
#include <map>

#include <Graphics/GraphicsResource.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentResourceManager
        {
        public:
            /**
            * Initializes a new instance of the ContentResourceManager
            */
            ContentResourceManager() = default;

            /**
            * Releases all resources being used by the ContentResourceManager class.
            */
            virtual ~ContentResourceManager() = default;

        public:
            template <class T>
            void AddResource(System::String name, std::shared_ptr<T> resource)
            {
                if (!this->HasResource(name))
                {
                    this->resources[name] = resource;
                }
            };

            template <class T>
            std::shared_ptr<T> GetResource(System::String name)
            {
                if (this->HasResource(name))
                {
                    return std::static_pointer_cast<T>(this->resources[name]);
                }

                return nullptr;
            };

            System::Boolean HasResource(System::String name)
            {
                return (this->resources.find(name) != this->resources.end());
            };

        private:
            ContentResourceManager(const ContentResourceManager& manager) = delete;
            ContentResourceManager& operator=(const ContentResourceManager& manager) = delete;

        private:
            std::map<System::String, std::shared_ptr<void>> resources;
        };
    }
}

#endif  /* GRAPHICSRESOURCEMANAGER_HPP */
