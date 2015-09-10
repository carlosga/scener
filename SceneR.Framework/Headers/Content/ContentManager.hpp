// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTMANAGER_HPP
#define CONTENT_CONTENTMANAGER_HPP

#include <memory>

#include <Content/ContentResourceManager.hpp>
#include <Framework/RendererServiceContainer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Model;
    }
}

namespace System
{
    namespace IO
    {
        class Stream;
    }
}

namespace SceneR
{
    namespace Content
    {
        /**
         * The ContentManager is used at runtime to load application content_manager from files.
         */
        class ContentManager final
        {
        private:
            static ContentResourceManager ResourceManager;

        public:
            /**
             * Initializes a new instance of the ContentManagerClass
             */
            ContentManager(SceneR::Framework::RendererServiceContainer& serviceProvider
                         , const std::u16string&                        rootDirectory);

            /**
             * Releases all resources being used by the ContentManager class.
             */
            ~ContentManager();

        public:
            /**
             * Gets the graphics device
             */
            SceneR::Framework::RendererServiceContainer& service_provider();

            /**
             * Gets the root directory associated with this ContentManager.
             */
            const std::u16string& root_directory();

        public:
            /**
             * Loads a the given asset.
             */
            std::shared_ptr<SceneR::Graphics::Model> load_model(const std::u16string& assetName) noexcept(false);

            /**
            * Disposes all data that was loaded by this ContentManager.
            */
            void unload();

        private:
            /**
             * Opens a stream for reading the specified asset.
             * #param assetName the name of the asset being read.
             */
            std::shared_ptr<System::IO::Stream> open_stream(const std::u16string& assetName) noexcept(false);

        private:
            SceneR::Framework::RendererServiceContainer& _service_provider;
            std::u16string                               _root_directory;
        };
    }
}

#endif  // CONTENT_CONTENTMANAGER_HPP
