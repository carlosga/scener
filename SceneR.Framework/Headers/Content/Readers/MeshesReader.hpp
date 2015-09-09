// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_MESHESREADER_HPP
#define CONTENT_READERS_MESHESREADER_HPP

#include <memory>
#include <string>

#include <Content/ContentTypeReader.hpp>
#include <Graphics/AttributeType.hpp>
#include <Graphics/ComponentType.hpp>
#include <Graphics/IndexElementSize.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class ModelMesh;
    }
}

namespace SceneR
{
    namespace Content
    {
        /**
         * Meshes reader
         */
        class MeshesReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the MeshesReader class.
             */
            MeshesReader();

            /**
             * Destructor
             */
            ~MeshesReader();

        public:
            /**
             * Reads the meshes contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;

        private:
            void read_mesh_part(const json11::Json&                          source
                              , ContentReaderContext&                        context
                              , std::shared_ptr<SceneR::Graphics::ModelMesh> mesh) const;

            SceneR::Graphics::IndexElementSize get_index_element_size(const SceneR::Graphics::ComponentType& type) const;

            SceneR::Graphics::VertexElementFormat get_vertex_element_format(const SceneR::Graphics::AttributeType& type) const;

            SceneR::Graphics::VertexElementUsage get_vertex_element_usage(const std::string& semantic) const;
        };
    }
}

#endif //CONTENT_READERS_MESHESREADER_HPP
