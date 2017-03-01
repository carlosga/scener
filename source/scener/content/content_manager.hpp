// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENT_MANAGER_HPP
#define SCENER_CONTENT_CONTENT_MANAGER_HPP

#include <memory>

#include <gsl/gsl>

#include "scener/content/content_resource_manager.hpp"

namespace scener::io { class file_stream; }

namespace scener::graphics
{
    class model;
    class service_container;
}

namespace scener::content
{
    /// The content_manager is used at runtime to load application content_manager from files.
    class content_manager final
    {
    public:
        /// Initializes a new instance of the content_manager class.
        /// \param serviceprovider the service provider that the content_manager should use to locate services.
        /// \param rootdirectory the root directory to search for content.
        content_manager(gsl::not_null<graphics::service_container*> serviceprovider, const std::string& rootdirectory) noexcept;

        /// Releases all resources being used by the content_manager class.
        ~content_manager();

    public:
        /// Gets the service provider that the content_manager should use to locate services.
        graphics::service_container* service_provider() const noexcept;

        /// Gets the root directory associated with this content_manager.
        const std::string& root_directory() const noexcept;

    public:
        /// Loads the given asset.
        std::shared_ptr<graphics::model> load(const std::string& assetname) noexcept;

        /// Disposes all data that was loaded by this content_manager.
        void unload() noexcept;

    private:
        std::shared_ptr<io::file_stream> open_stream(const std::string& assetname) noexcept;

    private:
        graphics::service_container* _service_provider;
        std::string                  _root_directory;
        content_resource_manager     _resource_manager;
    };
}

#endif // SCENER_CONTENT_CONTENT_MANAGER_HPP
