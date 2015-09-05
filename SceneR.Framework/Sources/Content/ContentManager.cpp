// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentManager.hpp>

#include <System/IO/FileStream.hpp>
#include <System/IO/File.hpp>
#include <System/IO/Path.hpp>
#include <System/IO/Stream.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::File;
        using System::IO::FileStream;
        using System::IO::Path;
        using System::IO::Stream;
        using SceneR::Framework::RendererServiceContainer;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::Model;

        ContentResourceManager ContentManager::ResourceManager;

        ContentManager::ContentManager(RendererServiceContainer& serviceProvider
                                     , const std::u16string&     rootDirectory)
            : _service_provider ( serviceProvider )
            , _root_directory   { rootDirectory }
        {
        }

        ContentManager::~ContentManager()
        {
            unload();
        }

        RendererServiceContainer& ContentManager::service_provider()
        {
            return _service_provider;
        }

        const std::u16string& ContentManager::root_directory()
        {
            return _root_directory;
        }

        std::shared_ptr<Model> ContentManager::load_model(const std::u16string& assetName)
        {
            auto& gdService = _service_provider.get_service<IGraphicsDeviceService>();
            auto& device    = gdService.graphics_device();
            auto  stream    = open_stream(assetName);

            ContentReader reader(assetName, device, *stream);

            auto isValid = reader.read_header();

            if (!isValid)
            {
                throw ContentLoadException("Requested file is not valid binary GLTF.");
            }

            return reader.read_asset();
        }

        void ContentManager::unload()
        {
            ResourceManager.clear();
        }

        std::shared_ptr<Stream> ContentManager::open_stream(const std::u16string& assetName) noexcept(false)
        {
            const auto filename  = assetName + u".bgltf";
            const auto path      = Path::combine(_root_directory, filename);

            if (!File::exists(path))
            {
                throw ContentLoadException("the asset file doesn't exists.");
            }

            return std::make_shared<FileStream>(path);
        }
    }
}
