// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERER_SERVICE_CONTAINER_HPP
#define SCENER_GRAPHICS_RENDERER_SERVICE_CONTAINER_HPP

#include <any>
#include <map>
#include <string>

namespace scener::graphics
{
    /// Renderer services container.
    ///
    /// Implementation references:
    ///  http://www.codinginlondon.com/2009/05/cheap-ioc-in-native-c.html
    ///  http://blog.jsolutions.co.uk/?p=588
    class service_container final
    {
    public:
        /// Adds a service to the RendererServiceContainer.
        template <class T>
        void add_service(T& service) noexcept
        {
            if (!is_registered<T>())
            {
                _instance_map[get_type_name<T>()] = &service;
            }
        }

        /// Gets the service object of the specified identifier.
        template <class T>
        T* get_service() const noexcept
        {
            if (!is_registered<T>())
            {
                throw std::runtime_error("Service not registered");
            }

            return (std::any_cast<T*>(_instance_map.find(get_type_name<T>())->second));
        }

        /// Removes the object providing a specified service.
        template <class T>
        void remove_service() noexcept
        {
            if (is_registered<T>())
            {
                _instance_map.erase(get_type_name<T>());
            }
        }

        void clear() noexcept
        {
            _instance_map.clear();
        }

    private:
        template <class T>
        bool is_registered() const noexcept
        {
            return (_instance_map.find(get_type_name<T>()) != _instance_map.end());
        }

        template <class T>
        std::string get_type_name() const noexcept
        {
            return typeid(T).name();
        }

    private:
        std::map<std::string, std::any> _instance_map;
    };
}

#endif // SCENER_GRAPHICS_RENDERER_SERVICE_CONTAINER_HPP
