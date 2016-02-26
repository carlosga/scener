// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP
#define SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP

#include "scener/content/readers/ContentTypeReader.hpp"

namespace scener { namespace content { namespace gltf { class BufferView; } } }

namespace scener { namespace content { namespace readers {

template <>
class ContentTypeReader<gltf::BufferView>
{
public:
    ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;
};

}}}

#endif // SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP
