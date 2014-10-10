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

#ifndef RENDERERSERVICECONTAINER_HPP
#define RENDERERSERVICECONTAINER_HPP

#include <map>
#include <memory>
#include <string>

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Renderer services container.
         *
         * Implementation references:
         *  http://www.codinginlondon.com/2009/05/cheap-ioc-in-native-c.html
         *  http://blog.jsolutions.co.uk/?p=588
         */
        class RendererServiceContainer
        {
        public:
            /**
             * Initializes a new instance of the RendererServiceContainer class.
             */
            RendererServiceContainer() = default;

            /**
             * Releases all the resources being used by this RendererServiceContainer.
             */
            ~RendererServiceContainer() = default;

        public:
            /**
             * Adds a service to the RendererServiceContainer.
             */
            template <class T>
            void AddService(T& service)
            {
                if (!this->IsRegistered<T>())
                {
                    this->instanceMap[this->GetTypeName<T>()] = static_cast<void*>(&service);
                }
            }

            /**
             * Gets the service object of the specified identifier.
             */
            template <class T>
            T& GetService()
            {
                if (!this->IsRegistered<T>())
                {
                    throw std::runtime_error("Service not registered");
                }

                return *(static_cast<T*>(this->instanceMap[this->GetTypeName<T>()]));
            };

            /**
             * Removes the object providing a specified service.
             */
            template <class T>
            void RemoveService()
            {
                if (this->IsRegistered<T>())
                {
                    this->instanceMap.erase(this->GetTypeName<T>());
                }
            };

        private:
            template <class T>
            System::Boolean IsRegistered()
            {
                return (this->instanceMap.find(this->GetTypeName<T>()) != this->instanceMap.end());
            };

            template <class T>
            std::string GetTypeName()
            {
                return typeid(T).name();
            };

        private:
            RendererServiceContainer(const RendererServiceContainer& serviceContainer) = delete;
            RendererServiceContainer& operator=(const RendererServiceContainer& serviceContainer) = delete;

        private:
            std::map<std::string, void*> instanceMap;
        };
    }
}

#endif /* RENDERERSERVICECONTAINER_HPP */
