// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_NODESREADER_HPP
#define CONTENT_READERS_NODESREADER_HPP

#include <map>
#include <memory>
#include <string>

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Node.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class InstanceSkin;
    }
}

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Node>
        {
        public:
            ContentTypeReader();

            ~ContentTypeReader();

        public:
            std::shared_ptr<SceneR::Graphics::Node> read(const std::pair<std::string, json11::Json>& source
                                                       , ContentReaderContext&                       context);

        private:
            std::shared_ptr<SceneR::Graphics::InstanceSkin> read_instance_skin(const json11::Json&   source
                                                                             , ContentReaderContext& context);
        };
    }
}

#endif //CONTENT_READERS_NODESREADER_HPP
