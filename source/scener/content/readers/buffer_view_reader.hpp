// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_BUFFER_VIEW_READER_HPP
#define SCENER_CONTENT_READERS_BUFFER_VIEW_READER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener::content::gltf { class buffer_view; }

namespace scener::content::readers
{
    template <>
    class content_type_reader<gltf::buffer_view>
    {
    public:
        content_type_reader() = default;

    public:
        auto read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const nlohmann::json& value) const noexcept;
    };
}

#endif // SCENER_CONTENT_READERS_BUFFER_VIEW_READER_HPP
