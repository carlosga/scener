// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_MODELMESHREADER_HPP
#define CONTENT_READERS_MODELMESHREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/AttributeType.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class EffectTechnique;
    }

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
            ContentTypeReader() = default;

            /**
             * Destructor
             */
            ~ContentTypeReader() = default;

        public:
            /**
             * Reads the meshes contents.
             */
            std::shared_ptr<SceneR::Graphics::ModelMesh> read(ContentReader*                              input
                                                            , const std::pair<std::string, json11::Json>& source);

        private:
            void read_mesh_part(ContentReader*                               input
                              , const json11::Json&                          source
                              , std::shared_ptr<SceneR::Graphics::ModelMesh> mesh) const;

            SceneR::Graphics::VertexElementFormat get_vertex_element_format(const SceneR::Graphics::AttributeType& type) const;

            SceneR::Graphics::VertexElementUsage get_vertex_element_usage(const std::string& semantic) const;

            std::shared_ptr<SceneR::Graphics::EffectTechnique> read_material(ContentReader*     input
                                                                           , const std::string& name) const;
        };
    }
}

#endif  // CONTENT_READERS_MODELMESHREADER_HPP
