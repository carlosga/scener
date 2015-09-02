// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTMANAGER_HPP
#define CONTENTMANAGER_HPP

#include <memory>

#include <System/IO/Stream.hpp>
#include <Content/ContentResourceManager.hpp>
#include <Content/ContentLoadException.hpp>
#include <Framework/RendererServiceContainer.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Model;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * The ContentManager is used at runtime to load application content from files.
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
            SceneR::Framework::RendererServiceContainer& ServiceProvider();

            /**
             * Gets the root directory associated with this ContentManager.
             */
            const std::u16string& RootDirectory();

        public:
            /**
             * Loads a the given asset.
             */
            std::shared_ptr<SceneR::GLTF::Model> LoadModel(const std::u16string& assetName) noexcept(false);

            /**
            * Disposes all data that was loaded by this ContentManager.
            */
            void Unload();

        private:
            /**
             * Opens a stream for reading the specified asset.
             * #param assetName the name of the asset being read.
             */
            std::shared_ptr<System::IO::Stream> OpenStream(const std::u16string& assetName) noexcept(false);

            /**
             * Low-level worker method that reads asset data.
             * @param assetName the name of the asset to be loaded from disk.
             */
            template <class T>
            std::shared_ptr<T> ReadAsset(const std::u16string& assetName) noexcept(false);

        private:
            SceneR::Framework::RendererServiceContainer& serviceProvider;
            std::u16string                               rootDirectory;
        };
    }
}

#endif  /* CONTENTMANAGER_HPP */
