// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_CONTENTTYPEREADER_HPP
#define SCENER_CONTENT_READERS_CONTENTTYPEREADER_HPP

#include <memory>
#include <string>

namespace json11 { class Json; }

namespace SceneR { namespace Content { class ContentReader; }}

namespace SceneR { namespace Content { namespace Readers {

/**
 * Interface for content type reader implementations.
 */
template <typename T>
class ContentTypeReader
{
public:
    /**
     * Initializes a new instance of the ContentTypeReader class.
     */
    ContentTypeReader() = default;

    /**
     * Releases all resources being used by this ContentTypeReader.
     */
    ~ContentTypeReader() = default;

public:
    /**
     * Reads a object from the current stream.
     */
    std::shared_ptr<T> read(ContentReader* input, const std::string& key, const json11::Json& source) const;
};

}}}

#endif // SCENER_CONTENT_READERS_CONTENTTYPEREADER_HPP