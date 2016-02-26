// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENTMANAGER_HPP
#define SCENER_CONTENT_CONTENTMANAGER_HPP

#include <memory>

#include <gsl.h>

#include "scener/content/ContentResourceManager.hpp"

namespace scener { namespace graphics {

class Model;
class RendererServiceContainer;

}}

namespace scener { namespace io { class FileStream; } }

namespace scener { namespace content {

/// The ContentManager is used at runtime to load application content_manager from files.
class ContentManager final
{
public:
    /// Initializes a new instance of the ContentManagerClass
    /// \param serviceProvider the service provider that the ContentManager should use to locate services.
    /// \param rootDirectory the root directory to search for content.
    ContentManager(gsl::not_null<graphics::RendererServiceContainer*> serviceProvider
                 , const std::string&                                 rootDirectory) noexcept;

    /// Releases all resources being used by the ContentManager class.
    ~ContentManager();

public:
    /// Gets the service provider that the ContentManager should use to locate services.
    graphics::RendererServiceContainer* service_provider() const noexcept;

    /// Gets the root directory associated with this ContentManager.
    const std::string& root_directory() const noexcept;

public:
    /// Loads the given asset.
    std::shared_ptr<graphics::Model> load(const std::string& assetName) noexcept;

    /// Disposes all data that was loaded by this ContentManager.
    void unload() noexcept;

private:
    std::shared_ptr<io::FileStream> open_stream(const std::string& assetName) noexcept;

private:
    graphics::RendererServiceContainer* _service_provider;
    std::string                         _root_directory;

    static ContentResourceManager resource_manager;
};

}}

#endif // SCENER_CONTENT_CONTENTMANAGER_HPP
