// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "ContentManager.hpp"

#include "ContentReader.hpp"
#include "ContentLoadException.hpp"
#include "../Graphics/Model.hpp"
#include "../Graphics/RendererServiceContainer.hpp"
#include "../IO/FileStream.hpp"
#include "../IO/File.hpp"
#include "../IO/Path.hpp"

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::Model;
        using SceneR::Graphics::RendererServiceContainer;
        using SceneR::IO::FileStream;

        ContentManager::ContentManager(gsl::not_null<RendererServiceContainer*> serviceProvider
                                     , const std::string&                       rootDirectory) noexcept
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

        std::shared_ptr<Model> ContentManager::load(const std::string& assetName) noexcept
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

        void ContentManager::unload() noexcept
        {
            resource_manager.clear();
        }

        std::shared_ptr<FileStream> ContentManager::open_stream(const std::string& assetName) noexcept
        {
            const auto filename  = assetName + ".gltf";
            const auto path      = SceneR::IO::Path::combine(_root_directory, filename);

            Ensures(SceneR::IO::File::exists(path));

            return std::make_shared<FileStream>(path);
        }

        ContentResourceManager ContentManager::resource_manager;
    }
}
