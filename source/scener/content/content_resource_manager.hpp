// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENT_RESOURCE_MANAGER_HPP
#define SCENER_CONTENT_CONTENT_RESOURCE_MANAGER_HPP

#include <memory>
#include <map>
#include <any>

#include "scener/graphics/graphics_resource.hpp"

namespace scener::content
{
    /// Content resource manager.
    class content_resource_manager final
    {
    public:
        /// Initializes a new instance of the ContentResourceManager
        content_resource_manager() = default;

        /// Releases all resources being used by the ContentResourceManager class.
        ~content_resource_manager() = default;

    public:
        /// Add the given resource to the resource manager.
        /// \param name the resource name.
        /// \param resource the resource to be added.
        template <typename T>
        void add_resource(const std::string& name, std::shared_ptr<T> resource)
        {
            if (!has_resource(name))
            {
                _resources[name] = resource;
            }
        }

        /// Gets the resource with the given name.
        /// \param name the resource name.
        /// \returns the resource; or nullptr if it does not exists.
        template <class T>
        std::shared_ptr<T> get_resource(const std::string& name) const
        {
            if (has_resource(name))
            {
                auto item = _resources.find(name)->second;
                if (item.has_value())
                {
                    return std::any_cast<std::shared_ptr<T>>(item);
                }
            }

            return nullptr;
        }

        /// Check if the given resource is in the resource manager.
        /// \param name the resource name.
        /// \returns true if the resource is present; otherwise false.
        bool has_resource(const std::string& name) const
        {
            return (_resources.find(name) != _resources.end());
        }

        /// Clears the resource manager instance.
        void clear()
        {
            if (_resources.size() > 0)
            {
                _resources.clear();
            }
        }

    private:
        content_resource_manager(const content_resource_manager& manager) = delete;
        content_resource_manager& operator=(const content_resource_manager& manager) = delete;

    private:
        std::map<std::string, std::any> _resources;
    };
}

#endif // SCENER_CONTENT_CONTENT_RESOURCE_MANAGER_HPP
