// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_PROGRAMSREADER_HPP
#define CONTENT_READERS_PROGRAMSREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Program.hpp>

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Program>
        {
        public:
            ContentTypeReader();

            ~ContentTypeReader();

        public:
            std::shared_ptr<SceneR::Graphics::Program> read(const std::pair<std::string, json11::Json>& value
                                                          , ContentReaderContext&                       context);
        };
    }
}
#endif //CONTENT_READERS_PROGRAMSREADER_HPP
