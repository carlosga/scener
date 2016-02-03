// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENTRESOURCEMANAGER_HPP
#define SCENER_CONTENT_CONTENTRESOURCEMANAGER_HPP

#include <memory>
#include <map>

#include "SceneR/Graphics/GraphicsResource.hpp"

namespace SceneR { namespace Content {

/// Content resource manager.
class ContentResourceManager final
{
public:
    /// Initializes a new instance of the ContentResourceManager
    ContentResourceManager() = default;

    /// Releases all resources being used by the ContentResourceManager class.
    ~ContentResourceManager() = default;

public:
    /// Add the given resource to the resource manager.
    /// \param name the resource name.
    /// \param resource the resource to be added.
    template <typename T>
    void add_resource(const std::string& name, std::shared_ptr<T> resource)
    {
        if (!has_resource(name))
        {
            _resources[name] = std::static_pointer_cast<void>(resource);
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
            return std::static_pointer_cast<T>(_resources.find(name)->second);
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
    ContentResourceManager(const ContentResourceManager& manager) = delete;
    ContentResourceManager& operator=(const ContentResourceManager& manager) = delete;

private:
    std::map<std::string, std::shared_ptr<void>> _resources;
};

}}

#endif // SCENER_CONTENT_CONTENTRESOURCEMANAGER_HPP
