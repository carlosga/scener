// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENT_MANAGER_HPP
#define SCENER_CONTENT_CONTENT_MANAGER_HPP

#include <memory>

#include <gsl.h>

#include "scener/content/content_resource_manager.hpp"

namespace scener { namespace graphics {

class Model;
class RendererServiceContainer;

}}

namespace scener { namespace io { class file_stream; } }

namespace scener { namespace content {

/// The content_manager is used at runtime to load application content_manager from files.
class content_manager final
{
public:
    /// Initializes a new instance of the content_manager class.
    /// \param serviceProvider the service provider that the content_manager should use to locate services.
    /// \param rootDirectory the root directory to search for content.
    content_manager(gsl::not_null<graphics::RendererServiceContainer*> serviceProvider
                 , const std::string&                                  rootDirectory) noexcept;

    /// Releases all resources being used by the content_manager class.
    ~content_manager();

public:
    /// Gets the service provider that the content_manager should use to locate services.
    graphics::RendererServiceContainer* service_provider() const noexcept;

    /// Gets the root directory associated with this content_manager.
    const std::string& root_directory() const noexcept;

public:
    /// Loads the given asset.
    std::shared_ptr<graphics::Model> load(const std::string& assetName) noexcept;

    /// Disposes all data that was loaded by this content_manager.
    void unload() noexcept;

private:
    std::shared_ptr<io::file_stream> open_stream(const std::string& assetName) noexcept;

private:
    graphics::RendererServiceContainer* _service_provider;
    std::string                         _root_directory;
    content_resource_manager            _resource_manager;
};

}}

#endif // SCENER_CONTENT_CONTENT_MANAGER_HPP
