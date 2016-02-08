// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP
#define SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace SceneR { namespace Content { namespace GLTF { class BufferView; } } }

namespace SceneR { namespace Content { namespace Readers {

template <>
class ContentTypeReader<GLTF::BufferView>
{
public:
    ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;
};

}}}

#endif // SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP
