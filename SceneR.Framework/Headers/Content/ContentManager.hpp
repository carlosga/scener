// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTMANAGER_HPP
#define CONTENTMANAGER_HPP

#include <memory>

#include <System/Core.hpp>
#include <System/IO/Stream.hpp>
#include <Content/ContentResourceManager.hpp>
#include <Content/ContentLoadException.hpp>
#include <Framework/RendererServiceContainer.hpp>

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
                         , const System::String&                        rootDirectory);

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
            const System::String RootDirectory();

        public:
            /**
             * Loads a the given asset.
             */
            template <class T>
            std::shared_ptr<T> Load(const System::String& assetName) noexcept(false);

            /**
            * Disposes all data that was loaded by this ContentManager.
            */
            void Unload();

        private:
            /**
             * Opens a stream for reading the specified asset.
             * #param assetName the name of the asset being read.
             */
            std::shared_ptr<System::IO::Stream> OpenStream(const System::String& assetName) noexcept(false);

            /**
             * Low-level worker method that reads asset data.
             * @param assetName the name of the asset to be loaded from disk.
             */
            template <class T>
            std::shared_ptr<T> ReadAsset(const System::String& assetName) noexcept(false);

        private:
            SceneR::Framework::RendererServiceContainer& serviceProvider;
            System::String                               rootDirectory;
        };
    }
}

#include <Content/ContentReader.hpp>

template <class T>
std::shared_ptr<T> SceneR::Content::ContentManager::Load(const System::String& assetName)
{
    return this->ReadAsset<T>(assetName);
}

template <class T>
std::shared_ptr<T> SceneR::Content::ContentManager::ReadAsset(const System::String& assetName)
{
    if (SceneR::Content::ContentManager::ResourceManager.HasResource(assetName))
    {
        return SceneR::Content::ContentManager::ResourceManager.GetResource<T>(assetName);
    }

    auto stream = this->OpenStream(assetName);
    SceneR::Content::ContentReader reader(assetName, *this, *stream);
    auto asset  = reader.ReadObject<T>();

    reader.ReadSharedResources();

    SceneR::Content::ContentManager::ResourceManager.AddResource<T>(assetName, asset);

    return asset;
}

#endif  /* CONTENTMANAGER_HPP */
