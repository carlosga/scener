// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_NODEREADER_HPP
#define SCENER_CONTENT_READERS_NODEREADER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener { namespace content { namespace gltf { class node; } } }

namespace scener { namespace content { namespace readers {

template <>
class content_type_reader<gltf::node>
{
public:
    content_type_reader() = default;

public:
    auto read(content_reader* input, const std::string& key, const json11::Json& source) const noexcept;
};

}}}

#endif // SCENER_CONTENT_READERS_NODEREADER_HPP
