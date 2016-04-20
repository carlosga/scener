// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/content_manager.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/graphics/model.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/io/file_stream.hpp"
#include "scener/io/file.hpp"
#include "scener/io/path.hpp"

namespace scener { namespace content {

using scener::graphics::model;
using scener::graphics::service_container;
using scener::io::file_stream;

content_manager::content_manager(gsl::not_null<service_container*> serviceprovider
                               , const std::string&                rootdirectory) noexcept
    : _service_provider { serviceprovider }
    , _root_directory   { rootdirectory }
{
}

content_manager::~content_manager()
{
    unload();
}

service_container* content_manager::service_provider() const noexcept
{
    return _service_provider;
}

const std::string& content_manager::root_directory() const noexcept
{
    return _root_directory;
}

std::shared_ptr<model> content_manager::load(const std::string& assetname) noexcept
{
    if (_resource_manager.has_resource(assetname))
    {
        return _resource_manager.get_resource<model>(assetname);
    }

    auto stream = open_stream(assetname);

    content_reader reader(assetname, this, *stream);

    auto asset = reader.read_asset();

    _resource_manager.add_resource<model>(assetname, asset);

    return asset;
}

void content_manager::unload() noexcept
{
    _resource_manager.clear();
}

std::shared_ptr<file_stream> content_manager::open_stream(const std::string& assetname) noexcept
{
    const auto filename  = assetname + ".gltf";
    const auto path      = scener::io::path::combine(_root_directory, filename);

    Ensures(scener::io::file::exists(path));

    return std::make_shared<file_stream>(path);
}

}}
