// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/buffer_view_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/buffer.hpp"
#include "scener/content/gltf/buffer_view.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;

auto content_type_reader<gltf::buffer_view>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto view = std::make_shared<gltf::buffer_view>();

    view->_name        = key;
    view->_buffer      = input->read_object<gltf::buffer>(source["buffer"].string_value());
    view->_byte_offset = static_cast<std::size_t>(source["byteOffset"].int_value());
    view->_byte_length = static_cast<std::size_t>(source["byteLength"].int_value());

    return view;
}

}}}
