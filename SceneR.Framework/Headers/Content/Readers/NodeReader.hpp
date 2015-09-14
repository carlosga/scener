// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_NODEREADER_HPP
#define CONTENT_READERS_NODEREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Node.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class InstanceSkin;
    }

    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Node>
        {
        public:
            ContentTypeReader();

            ~ContentTypeReader();

        public:
            std::shared_ptr<SceneR::Graphics::Node> read(ContentReader*                              input
                                                       , const std::pair<std::string, json11::Json>& source);

        private:
            std::shared_ptr<SceneR::Graphics::InstanceSkin> read_instance_skin(ContentReader*        input
                                                                             , const json11::Json&   source);
        };
    }
}

#endif //CONTENT_READERS_NODEREADER_HPP
