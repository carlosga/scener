// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_NODESREADER_HPP
#define CONTENT_READERS_NODESREADER_HPP

#include <map>
#include <memory>
#include <string>

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class InstanceSkin;
        class Node;
    }
}

namespace SceneR
{
    namespace Content
    {
        class NodesReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the NodesReader class.
             */
            NodesReader();

            /**
             * Destructor
             */
            ~NodesReader();

        public:
            /**
             * Reads the nodes contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;

        private:
            std::shared_ptr<SceneR::Graphics::Node> read_node(const std::pair<std::string, json11::Json>& source
                                                            , ContentReaderContext&                       context);

            std::shared_ptr<SceneR::Graphics::InstanceSkin> read_instance_skin(const json11::Json&   source
                                                                             , ContentReaderContext& context);
        };
    }
}

#endif //CONTENT_READERS_NODESREADER_HPP
