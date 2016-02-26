// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_ANIMATIONREADER_HPP
#define SCENER_CONTENT_READERS_ANIMATIONREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace scener { namespace graphics { class Animation; } }

namespace scener { namespace content { namespace readers {

template <>
class ContentTypeReader<graphics::Animation>
{
public:
    ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;
};

}}}

#endif // SCENER_CONTENT_READERS_ANIMATIONREADER_HPP
