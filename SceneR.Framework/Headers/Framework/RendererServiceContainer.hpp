// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_RENDERERSERVICECONTAINER_HPP
#define FRAMEWORK_RENDERERSERVICECONTAINER_HPP

#include <map>
#include <string>

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
        class RendererServiceContainer final
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
            void add_service(T& service)
            {
                if (!is_registered<T>())
                {
                    _instanceMap[get_type_name<T>()] = static_cast<void*>(&service);
                }
            }

            /**
             * Gets the service object of the specified identifier.
             */
            template <class T>
            T& get_service() const
            {
                if (!is_registered<T>())
                {
                    throw std::runtime_error("Service not registered");
                }

                return *(static_cast<T*>(_instanceMap.find(get_type_name<T>())->second));
            }

            /**
             * Removes the object providing a specified service.
             */
            template <class T>
            void remove_service()
            {
                if (is_registered<T>())
                {
                    _instanceMap.erase(get_type_name<T>());
                }
            }

            void clear()
            {
                _instanceMap.clear();
            }

        private:
            template <class T>
            bool is_registered() const
            {
                return (_instanceMap.find(get_type_name<T>()) != _instanceMap.end());
            }

            template <class T>
            std::string get_type_name() const
            {
                return typeid(T).name();
            }

        private:
            RendererServiceContainer(const RendererServiceContainer& serviceContainer) = delete;
            RendererServiceContainer& operator=(const RendererServiceContainer& serviceContainer) = delete;

        private:
            std::map<std::string, void*> _instanceMap;
        };
    }
}

#endif // FRAMEWORK_RENDERERSERVICECONTAINER_HPP
