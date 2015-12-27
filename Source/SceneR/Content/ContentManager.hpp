// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENTMANAGER_HPP
#define SCENER_CONTENT_CONTENTMANAGER_HPP

#include <memory>

#include <gsl.h>

#include "SceneR/Content/ContentResourceManager.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class Model;
        class RendererServiceContainer;
    }

    namespace IO
    {
        class FileStream;
    }

    namespace Content
    {
        /**
         * The ContentManager is used at runtime to load application content_manager from files.
         */
        class ContentManager final
        {
        public:
            /**
             * Initializes a new instance of the ContentManagerClass
             */
            ContentManager(gsl::not_null<SceneR::Graphics::RendererServiceContainer*> serviceProvider
                         , const std::string&                                         rootDirectory) noexcept;

            /**
             * Releases all resources being used by the ContentManager class.
             */
            ~ContentManager();

        public:
            /**
             * Gets the graphics device
             */
            SceneR::Graphics::RendererServiceContainer* service_provider() const noexcept;

            /**
             * Gets the root directory associated with this ContentManager.
             */
            const std::string& root_directory() const noexcept;

        public:
            /**
             * Loads a the given asset.
             */
            std::shared_ptr<SceneR::Graphics::Model> load(const std::string& assetName) noexcept;

            /**
            * Disposes all data that was loaded by this ContentManager.
            */
            void unload() noexcept;

        private:
            /**
             * Opens a stream for reading the specified asset.
             * #param assetName the name of the asset being read.
             */
            std::shared_ptr<SceneR::IO::FileStream> open_stream(const std::string& assetName) noexcept;

        private:
            static ContentResourceManager resource_manager;

        private:
            SceneR::Graphics::RendererServiceContainer* _service_provider;
            std::string                                 _root_directory;
        };
    }
}

#endif // SCENER_CONTENT_CONTENTMANAGER_HPP
