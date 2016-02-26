// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/content_manager.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/graphics/Model.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/io/file_stream.hpp"
#include "scener/io/file.hpp"
#include "scener/io/path.hpp"

namespace scener { namespace content {

using scener::graphics::Model;
using scener::graphics::RendererServiceContainer;
using scener::io::file_stream;

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
    if (_resource_manager.has_resource(assetName))
    {
        return _resource_manager.get_resource<Model>(assetName);
    }

    auto stream = open_stream(assetName);

    content_reader reader(assetName, this, *stream);

    auto asset = reader.read_asset();

    _resource_manager.add_resource<Model>(assetName, asset);

    return asset;
}

void content_manager::unload() noexcept
{
    _resource_manager.clear();
}

std::shared_ptr<file_stream> content_manager::open_stream(const std::string& assetName) noexcept
{
    const auto filename  = assetName + ".gltf";
    const auto path      = scener::io::path::combine(_root_directory, filename);

    Ensures(scener::io::file::exists(path));

    return std::make_shared<file_stream>(path);
}

}}
