// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_IMAGE_READER_HPP
#define SCENER_CONTENT_READERS_IMAGE_READER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener::content:: dds { class surface; }

namespace scener::content::readers
{
    template<>
    class content_type_reader<dds::surface>
    {
    public:
        content_type_reader() = default;

    public:
        auto read(content_reader* input, const std::string& key, const json11::Json& source) const noexcept;
    };
}

#endif  // SCENER_CONTENT_READERS_IMAGE_READER_HPP
