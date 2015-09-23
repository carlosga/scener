// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTMANAGER_HPP
#define CONTENT_CONTENTMANAGER_HPP

#include <memory>

#include <gsl.h>

#include <Content/ContentResourceManager.hpp>

namespace System
{
    namespace IO
    {
        class FileStream;
    }
}

namespace SceneR
{
    namespace Framework
    {
        class RendererServiceContainer;
    }

    namespace Graphics
    {
        class Model;
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
            ContentManager(Guide::not_null<SceneR::Framework::RendererServiceContainer*> serviceProvider
                         , const std::string&                                            rootDirectory);

            /**
             * Releases all resources being used by the ContentManager class.
             */
            ~ContentManager();

        public:
            /**
             * Gets the graphics device
             */
            SceneR::Framework::RendererServiceContainer* service_provider() const;

            /**
             * Gets the root directory associated with this ContentManager.
             */
            const std::string& root_directory() const;

        public:
            /**
             * Loads a the given asset.
             */
            std::shared_ptr<SceneR::Graphics::Model> load(const std::string& assetName) noexcept(false);

            /**
            * Disposes all data that was loaded by this ContentManager.
            */
            void unload();

        private:
            /**
             * Opens a stream for reading the specified asset.
             * #param assetName the name of the asset being read.
             */
            std::shared_ptr<System::IO::FileStream> open_stream(const std::string& assetName) noexcept(false);

        private:
            static ContentResourceManager resource_manager;

        private:
            SceneR::Framework::RendererServiceContainer* _service_provider;
            std::string                                  _root_directory;
        };
    }
}

#endif  // CONTENT_CONTENTMANAGER_HPP
