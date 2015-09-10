// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_MESHESREADER_HPP
#define CONTENT_READERS_MESHESREADER_HPP

#include <memory>
#include <string>

#include <Content/ContentTypeReader.hpp>
#include <Graphics/AttributeType.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Meshes reader
         */
        template<>
        class ContentTypeReader<SceneR::Graphics::ModelMesh>
        {
        public:
            /**
             * Initializes a news instance of the ContentTypeReader class.
             */
            ContentTypeReader();

            /**
             * Destructor
             */
            ~ContentTypeReader();

        public:
            /**
             * Reads the meshes contents.
             */
            std::shared_ptr<SceneR::Graphics::ModelMesh> read(const std::pair<std::string, json11::Json>& source
                                                            , ContentReaderContext&                       context);

        private:
            void read_mesh_part(const json11::Json&                          source
                              , ContentReaderContext&                        context
                              , std::shared_ptr<SceneR::Graphics::ModelMesh> mesh) const;

            SceneR::Graphics::VertexElementFormat get_vertex_element_format(const SceneR::Graphics::AttributeType& type) const;

            SceneR::Graphics::VertexElementUsage get_vertex_element_usage(const std::string& semantic) const;
        };
    }
}

#endif //CONTENT_READERS_MESHESREADER_HPP
