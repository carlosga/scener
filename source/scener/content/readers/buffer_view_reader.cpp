// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/buffer_view_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/buffer.hpp"
#include "scener/content/gltf/buffer_view.hpp"

namespace scener::content::readers
{
    using nlohmann::json;

    auto content_type_reader<gltf::buffer_view>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto view = std::make_shared<gltf::buffer_view>();

        view->_name        = key;
        view->_buffer      = input->read_object<gltf::buffer>(source["buffer"].get<std::string>());
        view->_byte_offset = source["byteOffset"].get<std::size_t>();
        view->_byte_length = source["byteLength"].get<std::size_t>();

        return view;
    }
}
