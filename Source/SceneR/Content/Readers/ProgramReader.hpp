// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_PROGRAMREADER_HPP
#define SCENER_CONTENT_READERS_PROGRAMREADER_HPP

#include "SceneR/Content/ContentTypeReader.hpp"
#include "SceneR/Graphics/Program.hpp"

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Program>
        {
        public:
            ContentTypeReader() = default;
            ~ContentTypeReader() = default;

        public:
            std::shared_ptr<SceneR::Graphics::Program> read(gsl::not_null<ContentReader*>               input
                                                          , const std::pair<std::string, json11::Json>& value) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_PROGRAMREADER_HPP
