// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_CONTENT_TYPE_READER_HPP
#define SCENER_CONTENT_READERS_CONTENT_TYPE_READER_HPP

#include <memory>
#include <string>

#include "nlohmann/json.hpp"

namespace scener::content { class content_reader; }

namespace scener::content::readers
{
    /// Interface for content type reader implementations.
    template <typename T>
    class content_type_reader
    {
    public:
        /// Initializes a new instance of the content_type_reader class.
        content_type_reader() = default;

    public:
        /// Reads a object from the current stream.
        std::shared_ptr<T> read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const nlohmann::json& value) const noexcept;
    };
}

#endif // SCENER_CONTENT_READERS_CONTENT_TYPE_READER_HPP
