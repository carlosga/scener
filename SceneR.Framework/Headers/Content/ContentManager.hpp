// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTMANAGER_HPP
#define CONTENTMANAGER_HPP

#include <memory>

#include "ContentResourceManager.hpp"
#include <Content/ContentLoadException.hpp>
#include <Content/ContentReader.hpp>
#include <System/IO/Stream.hpp>

namespace SceneR
{
    namespace Framework
    {
        class RendererServiceContainer;
    }
}

namespace SceneR
{
    namespace Content
    {
        /**
        * The ContentManager is used at runtime to load application content from files.
        */
        class ContentManager
        {
            static ContentResourceManager ResourceManager;

        public:
            /**
            * Initializes a new instance of the ContentManagerClass
            */
            ContentManager(SceneR::Framework::RendererServiceContainer& serviceProvider
                         , const System::String&                        rootDirectory);

            /**
            * Releases all resources being used by the ContentManager class.
            */
            virtual ~ContentManager();

        public:
            /**
            * Gets the graphics device
            */
            SceneR::Framework::RendererServiceContainer& ServiceProvider();

            /**
            * Gets the root directory associated with this ContentManager.
            */
            const System::String RootDirectory();

        public:
            /**
            * Loads a the given asset.
            */
            template <class T>
            std::shared_ptr<T> Load(const System::String& assetName) noexcept(false)
            {
                return this->ReadAsset<T>(assetName);
            }

            /**
            * Disposes all data that was loaded by this ContentManager.
            */
            void Unload();

        protected:
            /**
            * Opens a stream for reading the specified asset.
            * #param assetName the name of the asset being read.
            */
            virtual std::shared_ptr<System::IO::Stream> OpenStream(const System::String& assetName) noexcept(false);

        protected:
            /**
            * Low-level worker method that reads asset data.
            * @param assetName the name of the asset to be loaded from disk.
            */
            template <class T>
            std::shared_ptr<T> ReadAsset(const System::String& assetName) noexcept(false)
            {
                // if (ContentManager::ResourceManager.HasResource(assetName))
                // {
                //     return ContentManager::ResourceManager.GetResource<T>(assetName);
                // }

                auto stream = this->OpenStream(assetName);
                ContentReader reader(assetName, *this, *stream);
                auto asset  = reader.ReadObject<T>();

                reader.ReadSharedResources();

                // ContentManager::ResourceManager.AddResource<T>(assetName, asset);

                return asset;
            }

        private:
            SceneR::Framework::RendererServiceContainer& serviceProvider;
            System::String                               rootDirectory;
        };
    }
}

#endif  /* CONTENTMANAGER_HPP */
