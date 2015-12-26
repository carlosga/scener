// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_NODEREADER_HPP
#define SCENER_CONTENT_READERS_NODEREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Content/Readers/Node.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Skeleton;
    }

    namespace Content
    {
        template <>
        class ContentTypeReader<Node>
        {
        public:
            ContentTypeReader() = default;

            ~ContentTypeReader() = default;

        public:
            std::shared_ptr<Node> read(gsl::not_null<ContentReader*>               input
                                     , const std::pair<std::string, json11::Json>& source) const;

        private:
            std::shared_ptr<SceneR::Graphics::Skeleton> read_skeleton(gsl::not_null<ContentReader*> input
                                                                    , const json11::Json&           source) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_NODEREADER_HPP
