// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
            RendererServiceContainer()
            {
            }

            /**
             * Releases all the resources being used by this RendererServiceContainer.
             */
            ~RendererServiceContainer()
            {
            }

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
            }

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
            }

            void Clear()
            {
                this->instanceMap.clear();
            }

        private:
            template <class T>
            System::Boolean IsRegistered()
            {
                return (this->instanceMap.find(this->GetTypeName<T>()) != this->instanceMap.end());
            }

            template <class T>
            std::string GetTypeName()
            {
                return typeid(T).name();
            }

        private:
            RendererServiceContainer(const RendererServiceContainer& serviceContainer) = delete;
            RendererServiceContainer& operator=(const RendererServiceContainer& serviceContainer) = delete;

        private:
            std::map<std::string, void*> instanceMap;
        };
    }
}

#endif /* RENDERERSERVICECONTAINER_HPP */
