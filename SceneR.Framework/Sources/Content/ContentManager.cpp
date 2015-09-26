// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentManager.hpp>

#include <Content/ContentReader.hpp>
#include <Content/ContentLoadException.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/Model.hpp>
#include <System/IO/FileStream.hpp>
#include <System/IO/File.hpp>
#include <System/IO/Path.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Framework::RendererServiceContainer;
        using SceneR::Graphics::Model;
        using System::IO::FileStream;

        ContentManager::ContentManager(Guide::not_null<RendererServiceContainer*> serviceProvider
                                     , const std::string&                         rootDirectory)
            : _service_provider ( serviceProvider )
            , _root_directory   { rootDirectory }
        {
        }

        ContentManager::~ContentManager()
        {
            unload();
        }

        RendererServiceContainer* ContentManager::service_provider() const noexcept
        {
            return _service_provider;
        }

        const std::string& ContentManager::root_directory() const noexcept
        {
            return _root_directory;
        }

        std::shared_ptr<Model> ContentManager::load(const std::string& assetName)
        {
            if (resource_manager.has_resource(assetName))
            {
                return resource_manager.get_resource<Model>(assetName);
            }

            auto stream = open_stream(assetName);

            ContentReader reader(assetName, this, *stream);

            auto asset = reader.read_asset();

            resource_manager.add_resource<Model>(assetName, asset);

            return asset;
        }

        void ContentManager::unload()
        {
            resource_manager.clear();
        }

        std::shared_ptr<FileStream> ContentManager::open_stream(const std::string& assetName) noexcept(false)
        {
            const auto filename  = assetName + ".gltf";
            const auto path      = System::IO::Path::combine(_root_directory, filename);

            if (!System::IO::File::exists(path))
            {
                throw ContentLoadException("the asset file doesn't exists.");
            }

            return std::make_shared<FileStream>(path);
        }

        ContentResourceManager ContentManager::resource_manager;
    }
}
