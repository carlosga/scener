// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/content_manager.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/graphics/Model.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/io/FileStream.hpp"
#include "scener/io/File.hpp"
#include "scener/io/Path.hpp"

namespace scener { namespace content {

using scener::graphics::Model;
using scener::graphics::RendererServiceContainer;
using scener::io::FileStream;

content_manager::content_manager(gsl::not_null<RendererServiceContainer*> serviceProvider
                               , const std::string&                       rootDirectory) noexcept
    : _service_provider ( serviceProvider )
    , _root_directory   { rootDirectory }
{
}

content_manager::~content_manager()
{
    unload();
}

RendererServiceContainer* content_manager::service_provider() const noexcept
{
    return _service_provider;
}

const std::string& content_manager::root_directory() const noexcept
{
    return _root_directory;
}

std::shared_ptr<Model> content_manager::load(const std::string& assetName) noexcept
{
    if (resource_manager.has_resource(assetName))
    {
        return resource_manager.get_resource<Model>(assetName);
    }

    auto stream = open_stream(assetName);

    content_reader reader(assetName, this, *stream);

    auto asset = reader.read_asset();

    resource_manager.add_resource<Model>(assetName, asset);

    return asset;
}

void content_manager::unload() noexcept
{
    resource_manager.clear();
}

std::shared_ptr<FileStream> content_manager::open_stream(const std::string& assetName) noexcept
{
    const auto filename  = assetName + ".gltf";
    const auto path      = scener::io::Path::combine(_root_directory, filename);

    Ensures(scener::io::File::exists(path));

    return std::make_shared<FileStream>(path);
}

ContentResourceManager content_manager::resource_manager;

}}
