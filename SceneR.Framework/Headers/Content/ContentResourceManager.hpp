// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
